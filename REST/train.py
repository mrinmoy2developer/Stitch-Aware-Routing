import numpy as np
import torch
import os
import time
import math
from models.actor_critic import Actor, Critic
from utils.rsmt_utils import Evaluator
from utils.log_utils import *
import argparse
from utils.plot_curves import plot_curve

# Arguments
parser = argparse.ArgumentParser()
parser.add_argument('--experiment', type=str, default='DAC21', help='experiment name')
parser.add_argument('--degree', type=int, default=10, help='maximum degree of nets')
parser.add_argument('--dimension', type=int, default=2, help='terminal representation dimension')
parser.add_argument('--batch_size', type=int, default=4096, help='test batch size')
parser.add_argument('--eval_size', type=int, default=10000, help='eval set size')
parser.add_argument('--num_batches', type=int, default=40000, help='number of batches')
parser.add_argument('--seed', type=int, default=12, help='random seed')

# Optimizer
parser.add_argument('--learning_rate', type=float, default=2.5e-1)
parser.add_argument('--decay_rate', type=float, default=0.96)
parser.add_argument('--decay_iter', type=int, default=5000)

# Hardcoded
log_intvl = 100

args = parser.parse_args()

device = torch.device("cuda:0")
# device = torch.device("cpu")
print('experiment', args.experiment)
base_dir = 'save/'
exp_dir = base_dir + args.experiment + '/'
if not os.path.exists(exp_dir):
    os.makedirs(exp_dir)
    print('Created exp_dir', exp_dir)
else:
    print('Exp_dir', exp_dir, 'already exists')
last_deg=args.degree-1

for i in range(args.degree-1,2,-1):
    if os.path.exists(exp_dir + f'rsmt{i}b.pt'):
        print(f'Using previously trained weights from checkpoint{i}b.pt for progressive training')
        last_deg=i
        break
# print(last_deg)
for deg in range(last_deg+1,args.degree+1):
    print(f'Starting training for degree {deg}...')
    start_time = time.time()
    log_dir = exp_dir + 'rsmt' + str(deg) + '.log'
    ckp_dir = exp_dir + 'rsmt' + str(deg) + '.pt'
    last_ckp_dir = exp_dir + 'rsmt' + str(deg-1) + 'b.pt'
    best_ckp_dir = exp_dir + 'rsmt' + str(deg) + 'b.pt'
    divider=[1,2,4,4,8,8,8,16,16,16,16,16] # start with batch size 4096 are reduce it by a factor of 2 at 10,20,40,70,...
    batch_size=int(args.batch_size/divider[int(deg/10)])
    learning_rate=args.learning_rate*(args.decay_rate**(deg-3))
    loger = LogIt(log_dir)

    best_eval = 10.
    best_kept = 0

    actor = Actor(deg, device)
    critic = Critic(deg, device)
    mse_loss = torch.nn.MSELoss()
    optimizer = torch.optim.Adam(list(actor.parameters()) + list(critic.parameters()), lr=learning_rate, eps=1e-5)
    scheduler = torch.optim.lr_scheduler.ExponentialLR(optimizer=optimizer, gamma=args.decay_rate)
    evaluator = Evaluator()

    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    eval_cases = np.random.rand(args.eval_size,deg,args.dimension)
    seed=args.seed

    start_batch = 1
    if os.path.exists(ckp_dir):
        checkpoint = torch.load(ckp_dir)
        # checkpoint['batch_idx']=1
        start_batch = checkpoint['batch_idx'] + 1
        print("Checkpoint exists. Continue training from batch", start_batch, ".")
        best_eval = checkpoint['best_eval']
        actor.load_state_dict(checkpoint['actor_state_dict'])
        critic.load_state_dict(checkpoint['critic_state_dict'])
        optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        # change a seed so that different test cases will appear
        seed += start_batch % args.num_batches
        np.random.seed(seed)
        torch.manual_seed(seed)
    elif os.path.exists(last_ckp_dir):
        checkpoint = torch.load(last_ckp_dir)
        checkpoint['batch_idx']=1
        checkpoint['best_eval'] = 10
        start_batch = checkpoint['batch_idx'] + 1
        # print("ProgressivelCheckpoint exists. Continue training from batch", start_batch, ".")
        # best_eval = checkpoint['best_eval']
        actor.load_state_dict(checkpoint['actor_state_dict'])
        critic.load_state_dict(checkpoint['critic_state_dict'])
        optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        # change a seed so that different test cases will appear
        seed += start_batch % args.num_batches
        np.random.seed(seed)
        torch.manual_seed(seed)

    for batch_idx in range(start_batch, start_batch + args.num_batches):
        actor.train()
        critic.train()
        input_batch = np.random.rand(batch_size,deg, args.dimension)
        outputs, log_probs = actor(input_batch)
        predictions = critic(input_batch)
        
        lengths = evaluator.eval_batch(input_batch, outputs.cpu().detach().numpy(), deg)
        length_tensor = torch.tensor(lengths, dtype=torch.float).to(device)

        with torch.no_grad():
            disadvantage = length_tensor - predictions
        actor_loss = torch.mean(disadvantage * log_probs)
        critic_loss = mse_loss(predictions, length_tensor)
        loss = actor_loss + critic_loss

        optimizer.zero_grad()
        loss.backward()
        torch.nn.utils.clip_grad_norm_(actor.parameters(), 1.)
        torch.nn.utils.clip_grad_norm_(critic.parameters(), 1.)
        optimizer.step()
        # if iter < args.decay_iter:
        #     scheduler.step()

        if batch_idx % log_intvl == 0:
            print('[batch', str(batch_idx) + ',', 'time', str(int(time.time() - start_time)) + 's]')
            print('length ', lengths.mean())
            print('predict', predictions.cpu().detach().numpy().mean())
            actor.eval()
            eval_lengths = []
            for eval_idx in range(math.ceil(args.eval_size / batch_size)):
                eval_batch = eval_cases[batch_size * eval_idx : batch_size * (eval_idx + 1)]
                with torch.no_grad():
                    outputs, _ = actor(eval_batch, True)
                eval_lengths.append(evaluator.eval_batch(eval_batch, outputs.cpu().detach().numpy(), deg))
            eval_mean = np.concatenate(eval_lengths, -1).mean()
            if eval_mean < best_eval:
                best_eval = eval_mean
                best_kept = 0
                # keep a checkpoint anyway
                torch.save({
                    'batch_idx': batch_idx,
                    'best_eval': best_eval,
                    'actor_state_dict': actor.state_dict(),
                    'critic_state_dict': critic.state_dict(),
                    'optimizer_state_dict': optimizer.state_dict()
                }, best_ckp_dir)
                print('ckpt saved at', best_ckp_dir)
            else:
                best_kept += 1
            print('eval', eval_mean)
            print('best', best_eval, '(' + str(best_kept) + ')')
            
            print(outputs[0].cpu().detach().numpy().reshape(-1, 2).transpose(1, 0))

            loger.log_iter(batch_idx, {'eval' : eval_mean, 'best' : best_eval, 'time' : int(time.time() - start_time)})

    torch.save({
        'batch_idx': batch_idx,
        'best_eval': best_eval,
        'actor_state_dict': actor.state_dict(),
        'critic_state_dict': critic.state_dict(),
        'optimizer_state_dict': optimizer.state_dict()
    }, ckp_dir)
    print('ckpt saved at', ckp_dir)

    # plot_curve(log_dir)
