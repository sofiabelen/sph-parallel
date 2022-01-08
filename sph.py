import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt('data/xyz270.csv', names=True, delimiter=',')

n = 10
R = 3526229
# aplha = R*10^-11*{0.15, 0.25, 0.5, 1}
alpha = R * 10**(-11)

def grid_ij(i, j):
    return -R + i / (n - 1) * 2 * R, -R + j / (n - 1) * 2 * R

grid = np.zeros((n, n))

for i in range(n):
    for j in range(n):
        xij, zij = grid_ij(i, j)

        for k in range(len(data)):
            x = data['x'][k]
            z = data['z'][k]
            y = data['y'][k]

            grid[i][j] += data['density'][k] *\
                    np.exp(-alpha * np.sqrt((x - xij)**2 +\
                    (z - zij)**2 + (y - 0)**2))

print(grid)

x = np.arange(n)
z = np.arange(n)

fig, ax = plt.subplots()
c = ax.pcolormesh(x, z, grid, cmap='RdBu')
ax.set_title('pcolormesh')

# ax.axis([x.min(), x.max(), y.min(), y.max()])
fig.colorbar(c, ax=ax)

# fig.savefig("img/graph1.png", dpi=200)
# plt.show()
