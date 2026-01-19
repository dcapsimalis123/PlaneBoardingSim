import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as am
import matplotlib
from mpl_toolkits.axes_grid1.anchored_artists import AnchoredDrawingArea
import pandas as pd
import os, sys

# PSUEDO
# Read in file
#   a) open file
#   b) read as a n person x length dimensional array
#   c) close file
# assign colors to each person
# plot vs time with gif creation tool in matplotlib
fig, ax = plt.subplots()

def main():
    output, passengerCount = read_in_info(sys.argv[1])
    animation_block(passengerCount, output)

class Person:
    def __init__(self,radius=0.15,color='r',x=0,y=-1):
        self.patch = matplotlib.patches.Circle((x, y), radius=radius)
        self.patch.set(color=color)
        self.patch.set_animated(True)
        ax.add_artist(self.patch)

    def update_position(self, x, y):
        self.patch.set(center=(x,y))



def animation_block(passengerCount, data):
    people = [ Person(color='r', x=-1, y=-1) for i in range(passengerCount) ]

    ax.set_xlim(0,5)
    ax.set_ylim(0,30)

    step_count = 14

    def init():
        for person in people:
            person.patch.set(center=(-1,-1))
        return tuple(person.patch for person in people)

    def update(frame):
        for i, person in enumerate(people):
            person.update_position(data[frame, i*2],data[frame, i*2+1])
        return tuple(person.patch for person in people)

    anim = am.FuncAnimation(fig, update, interval = 1000, frames = step_count, init_func = init,  blit = True)
    plt.show()

def read_in_info(pathToFile):
    if not os.path.exists(pathToFile):        
        raise FileNotFoundError(f"Invalid path: {pathToFile}")
    output = np.array(pd.read_csv(pathToFile))
    return output[2:].astype(np.float64), output[0,-2].astype(np.int32)+1

main()

