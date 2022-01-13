import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from scipy.optimize import curve_fit

def line(x, a, b):
    return a*x + b

mpi = np.genfromtxt('times-mpi.csv', names=True)
acc = np.genfromtxt('times-acc.csv', names=True)
acc_mem = np.genfromtxt('times-acc-mem.csv', names=True)

mpi_time = np.zeros(int(len(mpi) / 4))
acc_time = np.zeros(int(len(mpi) / 4))
acc_mem_time = np.zeros(int(len(mpi) / 4))
n_arr = np.zeros(int(len(mpi) / 4))

for i in range(int(len(mpi) / 4)):
    time_mpi = 0
    time_acc = 0
    time_acc_mem = 0
    err_mpi = 0
    err_acc = 0
    err_acc_mem = 0
    for k in range(4):
        time_mpi += mpi['t'][i * 4 + k]
        time_acc += acc['t'][i * 4 + k]
        time_acc_mem += acc_mem['t'][i * 4 + k]

    time_mpi /= 4
    time_acc /= 4
    time_acc_mem /= 4

    for k in range(4):
        err_mpi += (mpi['t'][i * 4 + k] - time_mpi)**2
        err_acc += (acc['t'][i * 4 + k] - time_acc)**2
        err_acc_mem += (acc_mem['t'][i * 4 + k] - time_acc_mem)**2

    err_mpi = np.sqrt(err_mpi)
    err_acc = np.sqrt(err_acc)
    err_acc_mem = np.sqrt(err_acc_mem)
    err_mpi /= 4
    err_acc /= 4
    err_acc_mem /= 4

    mpi_time[i] = time_mpi
    acc_time[i] = time_acc
    acc_mem_time[i] = time_acc_mem
    n_arr[i] = mpi['n'][i * 4]

    print(format(mpi['n'][i * 4], ".0f"), "&",
            format(time_mpi, ".2f"), r"$\pm$",
            format(err_mpi, ".2f"), "&",
            format(time_acc, ".2f"), r"$\pm$",
            format(err_acc, ".2f"), r"&",
            format(time_acc_mem, ".2f"), r"$\pm$",
            format(err_acc_mem, ".2f"), r"\\ \hline")


# popt, pcov = curve_fit(f=line, xdata=data['x'], ydata=data['y'])
# 
# print(popt[0])
# print(pcov)

sns.set(context='talk', style='darkgrid')
fig, ax = plt.subplots(figsize=(10, 9))

ax.set_xlabel(r'$n_x \cdot n_z$')
ax.set_ylabel(r'time, ms')

ax.plot(n_arr[:4]**2, mpi_time[:4], '--o', label='MPI 48 processes')
ax.plot(n_arr[:4]**2, acc_time[:4], '--o', label='OpenACC Nvidia Titan V using Unified Memory')
ax.plot(n_arr[:4]**2, acc_mem_time[:4], '--o', label='OpenACC Nvidia Titan V')

ax.legend()

# fig.savefig("img/time.pdf")
fig.savefig("img/time-small.pdf")
plt.show()
