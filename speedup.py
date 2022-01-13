import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from scipy.optimize import curve_fit

M = 65536 

# def T_arith(N, P):
#     return N**2 / P * M * T
# 
# def T_comm(N, P):
#     return (alpha + N**2 / P / beta) * np.sqrt(P)
# 
# def T_paral(N, P):
#     if P == 1:
#         return T_arithm(N, P)
#     return T_arithm(N, P) + T_comm(N, P)

def S(P, T, beta, alpha):
    M = 65536 
    N = 100
    return (N**2 * M * T) /\
            (N**2 / P * M * T +\
            (alpha + N**2 / P / beta) * np.sqrt(P))
    # return (tau * N * ( 2 * N + 1)) / (
    #         (alpha + N / P / beta * 64 / 2) * np.sqrt(P)
    #         + tau * N * ( 2 * N / P + 1))

data = np.genfromtxt('mpi-speedup.csv', names=True)

p = data['p']
t = data['t']

sp = t[0] / t
ep = t[0] / t / p

alpha = 4.27e-9
tau = 1.56e-9 * 100
beta = 5e7
popt, pcov = curve_fit(f=S, xdata=p, ydata=sp,
        p0=[tau, beta, alpha])

print("T")
print("beta")
print("alpha")

print("{:.2E}".format(popt[0]), r"$\pm$",
        "{:.2E}".format(pcov[0][0]**0.5))
print("{:.2E}".format(popt[1]), r"$\pm$",
        "{:.2E}".format(pcov[1][1]**0.5))
print("{:.2E}".format(popt[2]), r"$\pm$",
        "{:.2E}".format(pcov[2][2]**0.5))



sns.set(context='talk', style='darkgrid')
fig, axs = plt.subplots(1, 2, figsize=(12, 6))

axs[0].set_xlabel(r'Number of processes')
axs[1].set_xlabel(r'Number of processes')
# ax.set_ylabel(r'$$')

sp_th = S(p, *popt)
ep_th = S(p, *popt) / p

axs[0].plot(data['p'], sp, '--o', label='Speedup')
axs[0].plot(data['p'], sp_th, '--o', label='Speedup - fitting')
axs[1].plot(data['p'], ep, '--o', label='Efficiency')
axs[1].plot(data['p'], ep_th, '--o', label='Efficiency - fitting')

axs[0].legend()
axs[1].legend()

fig.savefig("img/speedup-mpi.pdf")
# plt.show()
