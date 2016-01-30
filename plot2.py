import matplotlib.pyplot as plt

plt.title('Throughput v.s Number of Blocks (K) for Burst Error Model\n for e = 0.0005')
plt.ylabel("Throughput")
plt.xlabel("K")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="(N=5000,B=50)")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="(N=1000,B=50)")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="(N=5000,B=500)")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="(N=1000,B=500)")
plt.errorbar(100, 0.5, yerr=0.1, xerr=0.2)
# Place a legend to the right of this smaller figure.
plt.legend(bbox_to_anchor=(1.05, 1), loc=1, borderaxespad=0.)

plt.show()
