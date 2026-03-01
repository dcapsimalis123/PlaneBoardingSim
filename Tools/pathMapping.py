import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os, sys



def read_in_data(csvName, person):
    """ This function will read in the data we want 
    from the files expected format for ease of analysis
    This should make scaling easy, this will need to be update
    new format as we update the output function in the sim."""
    tempCSV = np.array(pd.read_csv(csvName,skiprows=1))
    return tempCSV[2:,person*2:person*2+2].astype(np.float64)

def plot_data(data,color=[1,0,0]):
    """ This function takes data output from read in and plots the
    simplest form of output from it"""
    plt.plot(data[:,1],data[:,0],color)

def read_in_individual(person,color):
    """"This function will agregate for each person for ease of iteration"""
    data = read_in_data(sys.argv[1],person)
    plot_data(data,color)

def main():
    for i in range(48):
        read_in_individual(i,[i/48,0,(1-i/48)])
    plt.show()


if __name__ == "__main__":
    main()