import matplotlib.pyplot as plt

plt.title('Throughput v.s Number of Blocks (K) for Independent Error Model')
plt.ylabel("Throughput")
plt.xlabel("K")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="e=0.0001")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="e=0.0003")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="e=0.0005")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="e=0.0007")
plt.plot([0,1,2,10,40,100,400,1000], [0.9248,0.92448,0.94784, 0.95856, 0.92256, 0.86032, 0.708, 0.568], label="e=0.001")
# Place a legend to the right of this smaller figure.
plt.legend(bbox_to_anchor=(1.05, 1), loc=1, borderaxespad=0.)

plt.show()
