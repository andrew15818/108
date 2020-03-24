import numpy as np 
import pandas as pd
import time
from random import * 
import matplotlib.pyplot as plt 

ITERATIONS = 100
LEARNING_RATE = 1e-4
'''
Homework has to follow PEP8 guidelines, including them here for quick reference: 
    Naming Conventions:
        function: all lowercase, use underscore for multiple words
        variable: same, use underscore; make it descriptive
        class: each word should start with uppercase, don't use underscore
        method: all lowercase, use udnerscores for readability.
        constant: all caps, should use underscores for mult. words       
'''
#returns quite a large negative number, which I suppose 
#should be the case if we have a small learning rate
def gradient(xtrain, ytrain,slope, num_points):
        #print('hola')
        tmp = 0
        #target-prediction * prediction basically
        for i in range(0, num_points):
                tmp += (ytrain[i]-(slope*xtrain[i]))*xtrain[i]
        
        return tmp

def mean_squared_error(error_list, num_points):
    return (np.sum(error_list)/num_points)

def model(xtrain, ytrain):
    #we need several values: w0(weight), gradient, yi(guess),...

#import the data from the csv, x and y values
train_df = pd.read_csv("train_data.csv")

#rows and columns of the training data.
xtrain = train_df['x_train']
ytrain = train_df['y_train']

model(xtrain, ytrain)
'''
Basically: we can use a function of the form f(x) = b0+b1(x),
to predict the values for the data points. We first randomize the input
values, and measure the losss against the actual function values. We should
see the loss go down after a few 'iterations'. Does iterations mean iterations
through the whole data set or just individual points from the dataset?
'''

#generating and showing the graphs
plt.plot(xtrain,ytrain,'.')
plt.show()
print("We're making it to the end :D")
