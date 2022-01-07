import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

grid = np.genfromtxt('grid.csv')
print(grid)

x = np.arange(len(grid))
z = np.arange(len(grid))

fig, ax = plt.subplots()
c = ax.pcolormesh(x, z, grid, cmap='RdBu')
ax.set_title('pcolormesh')

# ax.axis([x.min(), x.max(), y.min(), y.max()])
fig.colorbar(c, ax=ax)

fig.savefig("img/graph++.png", dpi=200)
plt.show()
