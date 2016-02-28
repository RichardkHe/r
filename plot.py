#!/usr/bin/env python
# a bar plot with errorbars
import numpy as np
import matplotlib.pyplot as plt

N = 5
#Number of Transmissions:
LinkState_Tx = (12, 14, 12, 10, 100)
DistanceVector_Tx = (10, 10.9091, 14, 9.09091, 10)
HotPotatoeI_Tx = (56.9091, 56.2182, 72.9182, 95, 59.4182)
HotPotatoeI_Tx_Std = (4.09, 2.21, 3.233, 6.0769, 4.12)
HotPotatoeII_Tx = (44.9818, 42.6545, 61.0091, 57.9818, 10)
HotPotatoeII_Tx_Std = (1.63, 1.2168, 4.31, 4.47, 0)

#PathLengths:
LinkState_PathLength = (2.72727,2.36364,2.76033,2.64463,0.909091)
DistanceVector_PathLength = (2.72727,2.36364,2.76033,2.64463,0.909091)
HotPotatoeI_PathLength = (5.69091,4.60727,3.56545,2.90909,3.20182)
HotPotatoeI_PathLength_Std = (0.409,0.28,0.095,0,0.2)
HotPotatoeII_PathLength = (4.49818,3.90364,3.33818,2.90909,1)
HotPotatoeII_PathLength_Std = (0.168,0.125,0.058,0,0)

ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

fig, ax = plt.subplots()
#Transmissions:
#rects1 = ax.bar(ind, LinkState_Tx, width, color='c')
#rects2 = ax.bar(ind + width, DistanceVector_Tx, width, color='m')
#rects3 = ax.bar(ind + 2*width, HotPotatoeI_Tx, width, color='lightgreen', yerr=HotPotatoeI_Tx_Std)
#rects4 = ax.bar(ind + 3*width, HotPotatoeII_Tx, width, color='lightblue', yerr=HotPotatoeII_Tx_Std)


#PathLengths:
rects1 = ax.bar(ind, LinkState_PathLength, width, color='c')
rects2 = ax.bar(ind + width, DistanceVector_PathLength, width, color='m')
rects3 = ax.bar(ind + 2*width, HotPotatoeI_PathLength, width, color='lightgreen', yerr=HotPotatoeI_PathLength_Std)
rects4 = ax.bar(ind + 3*width, HotPotatoeII_PathLength, width, color='lightblue', yerr=HotPotatoeII_PathLength_Std)

#Transmissions:
# add some text for labels, title and axes ticks
#ax.set_ylabel('Number of Average Transmissions')
#ax.set_ylim([0,110])
#ax.set_title('Number of Transmissions required to set up the networks\n v.s the Topology of the Network')

#PathLengths:
ax.set_ylabel('Average Path Lengths')
ax.set_title('Average path lengths of the Network\n v.s the Topology of the Network')

ax.set_xlabel('Graphs along with their corresponding degrees')
ax.set_xticks(ind + 2*width)
ax.set_xticklabels(('Graph1 (2)', 'Graph2 (2.18)', 'Graph3 (2)', 'Graph4 (1.82)', 'Graph5 (10)'))
ax.legend((rects1[0], rects2[0], rects3[0], rects4[0]), ('LinkState', 'DistanceVector', 'HotPotato I', 'HotPotato II'), loc = 1, title ="Routing Algorithms")


def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., height,
                '%.1f' % height,
                ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)
autolabel(rects3)
autolabel(rects4)

plt.show()
