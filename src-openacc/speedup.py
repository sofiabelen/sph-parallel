import numpy as np

data = np.genfromtxt('times.csv', names=True)

seq = [101.025, 2524.48, 10097.8, 1.01002e+06]
n = data['n']
t = data['t']

i = 0
times = np.zeros(4)
for k in range(len(n)):
    times[i] += t[k]
    if k > 0 and n[k] != n[k - 1]:
        i += 1

times /= 4

for k in range(len(times)):
    print(times[k])

for k in range(len(times)):
    print(seq[k] / times[k])
