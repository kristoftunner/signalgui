import numpy as np
from matplotlib import pyplot as plt

phi = 0
fs = 10
N = 10
t = np.arange(0, 1/fs*N*np.pi*2, 1/fs)
x = np.exp(1j*t).real
plt.plot(x)
plt.show()