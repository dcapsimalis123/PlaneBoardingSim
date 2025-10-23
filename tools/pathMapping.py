import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os, sys



def read_in_data(csvName, person):
    tempCSV = np.array(pd.read_csv(csvName,skiprows=1))
    return tempCSV[2:,person*2:person*2+2].astype(np.float64)

def plot_data(data):
    plt.plot(data[:,1],data[:,0])
    plt.show()


data = read_in_data('tools\output.csv',1)
plot_data(data)