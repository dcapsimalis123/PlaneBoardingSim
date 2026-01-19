import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as am
import matplotlib
from mpl_toolkits.axes_grid1.anchored_artists import AnchoredDrawingArea
import pandas as pd
import os, sys

# PSEUDOCODE
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
    """
    Represents individual passenger with circle patch on the plot.
    """
    def __init__(self,radius=0.15,color='r',x=0,y=-1):
        self.patch = matplotlib.patches.Circle((x, y), radius=radius)
        self.patch.set(color=color)
        self.patch.set_animated(True)
        ax.add_artist(self.patch)

    def update_position(self, x, y):
        self.patch.set(center=(x,y))



def animation_block(passengerCount, data):
    """
    Takes processed data, initializes class objects for animation, and executes animation loop.

    Args:
        passengerCount: number of passengers
        data: raw unassociated data from csv
    """
    people = [ Person(color='r', x=-1, y=-1) for i in range(passengerCount) ]

    # Set to fit the size of the plane
    ax.set_xlim(0,5)
    ax.set_ylim(0,30)

    # Derived from data shape
    step_count = data.shape[1]

    def init():
        # This is the default value setter for all patch objects, it is required for blitting
        for person in people:
            person.patch.set(center=(-1,-1))
        return tuple(person.patch for person in people)

    def update(frame):
        # This updates the position of each patch based on its associated part of the data frame.
        # TODO: make dynamic column tracking to replace magic numbers i and 2 as in i*2 - relates to read_in_info expansion
        for i, person in enumerate(people):
            person.update_position(data[frame, i*2],data[frame, i*2+1])
        return tuple(person.patch for person in people)

    # executes animation loop, set interval to lower if we have more granular time steps, but that will likely be a system argument of the system
    # TODO: have sim automatic run of this script have that as a system argument based on the interval value of sim step speed.
    anim = am.FuncAnimation(fig, update, interval = 1000, frames = step_count, init_func = init,  blit = True)
    plt.show()

def read_in_info(pathToFile):
    """
    Read passenger data from CSV file.
    
    Returns: 
        tuple: (position_data array, passenger_count)
    """
    # TODO: Likely the to do information in update will be an expansion of these functions.
    if not os.path.exists(pathToFile):        
        raise FileNotFoundError(f"Invalid path: {pathToFile}")
    output = np.array(pd.read_csv(pathToFile, header=None))
    return output[2:].astype(np.float64), int(output[0,-2])+1

main()

