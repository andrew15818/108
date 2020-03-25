import numpy as np 
import pandas as pd
import time
from random import randrange
import matplotlib.pyplot as plt 

#constants
ITERATIONS = 100
LEARNING_RATE = 1e-4
SLOPE_GRADIENT = 1
INT_GRADIENT = 2

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
def gradient(type, ytrain, xtrain, slope, intercept, num_points):
    tmp = 0
    if type == SLOPE_GRADIENT:
        for i in range(0, num_points):
            tmp += (ytrain[i] - slope*xtrain[i] - intercept) * xtrain[i] 
    elif type == INT_GRADIENT:
        for i in range(0, num_points):
            tmp += (ytrain[i] - slope*xtrain[i] - intercept)
    return (-(2 / num_points)) * tmp

#get the average error value, just for debugging
def mse(ytrain,predictions, num_points):
    tmp = 0
    for i in range(0, num_points):
        tmp +=(ytrain[i] - predictions[i,0])**2
    return tmp / num_points

def model(xtrain, ytrain):
    #we need several values: w0(weight), gradient, yi(guess),...
    #Then the MSE function should be used to find the slope and intercept?
    num_points = xtrain.size
    #two values we want to optimize, init to random values first
    slope = randrange(1,5)
    intercept = randrange(1,5)

    predictions = np.zeros((num_points,1))
    error = np.zeros((num_points,1))
    for i in range(0, ITERATIONS):
        for j in range(0, num_points):
            predictions[j, 0] = intercept + slope * xtrain[j]        

        slope = slope - gradient(SLOPE_GRADIENT, ytrain, 
                                xtrain, slope, intercept, 
                                num_points)*LEARNING_RATE
        intercept = intercept - gradient(INT_GRADIENT, ytrain, xtrain,
                                        slope, intercept, num_points)*LEARNING_RATE
        print(mse(ytrain, predictions, num_points))
        plt.plot(xtrain, predictions)

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
