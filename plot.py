import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

n_arr = [10, 50, 100, 1000]

for k in range(4):
    grid = np.genfromtxt("data/grid" + str(n_arr[k]) + ".csv")
    # print(grid)
    
    x = np.arange(len(grid))
    z = np.arange(len(grid))
    
    fig, ax = plt.subplots()
    # cb.solids.set_rasterized(True)
    c = ax.pcolormesh(x, z, grid, cmap="magma",linewidth=0,rasterized=True)
    # ax.set_title('pcolormesh')
    
    # ax.axis([x.min(), x.max(), y.min(), y.max()])
    fig.colorbar(c, ax=ax)
    
    fig.savefig("img/graph" + str(n_arr[k]) + ".png", dpi=200)
    fig.savefig("img/graph" + str(n_arr[k]) + ".pdf")
    plt.show()
