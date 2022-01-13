import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns


R = 3526229
n_arr = [10, 20, 50, 100, 250, 500, 750, 1000]
alpha_arr = [R * 10**(-11) * 0.15,
             R * 10**(-11) * 0.25,
             R * 10**(-11) * 0.5,
             R * 10**(-11) * 0.1]
coef_arr = [0.15, 0.25, 0.5, 0.1]

sns.set_context("talk")

for k in range(2):
    for p in range(4):
        grid = np.genfromtxt("data-openacc/grid" + str(n_arr[k])
                + "-" + str(p) + ".csv")
        
        x = np.arange(len(grid))
        z = np.arange(len(grid))
        
        fig, ax = plt.subplots()
        c = ax.pcolormesh(x, z, grid, cmap="magma",
                linewidth=0, rasterized=True)
        ax.set_title(r'$\alpha = R \cdot 10^{-11} \cdot $'
                + str(coef_arr[p]) + ", n = " + str(n_arr[k]))
        
        fig.colorbar(c, ax=ax)
        
        fig.savefig("img-openacc/graph" + str(n_arr[k]) + "-"
                + str(p) + ".png", dpi=200)
        fig.savefig("img-openacc/graph" + str(n_arr[k]) + "-"
                + str(p) + ".pdf")
# plt.show()
