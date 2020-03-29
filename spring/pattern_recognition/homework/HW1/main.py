import numpy as np 
import pandas as pd
import time
from random import randrange
import matplotlib.pyplot as plt 

#constants
ITERATIONS = 100
LEARNING_RATE = 1e-2
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
    tmp = np.sum((ytrain - predictions) **2)
    return (tmp/num_points)

#returns the predicted values for the input set.
def model(xtrain, ytrain):
    #values we try to maximize
    slope = 0
    intercept = 0 

    #here we store the values we will  use to 
    #plot the loss_array
    loss_array = []
    it_count = []

    #turning the two original objects into 
    #numpy arrays
    X = np.array(xtrain)
    Y_original = np.array(ytrain)
    num_points = X.shape[0] #number of testing points

    for i in range(0,ITERATIONS):
        Y_predict = slope * X + intercept
        slope_gradient = (-2/num_points) * np.sum(X * (Y_original - Y_predict))
        int_gradient = (-2/num_points) * np.sum(Y_original - Y_predict)
        
        slope = slope - slope_gradient * LEARNING_RATE
        intercept = intercept - int_gradient * LEARNING_RATE

        loss_array.append(mse(ytrain, Y_predict, num_points))
        it_count.append(i)
    
    print('slope: '+str(slope)+'\tintercept: '+str(intercept))
    return Y_predict,loss_array,it_count

#import the data from the csv, x and y values
train_df = pd.read_csv("train_data.csv")

##Uncomment these lines for the training data graph #xtrain = train_df['x_train']
#ytrain = train_df['y_train']
#Y_predict, loss_array, it_count = model(xtrain,ytrain)
#plt.plot(xtrain,ytrain,".")             #training points
#plt.plot(it_count, loss_array,'.',label='training data error')
#plt.title('training data error')
#plt.show()

#handling the test data

train_df = pd.read_csv("test_data.csv")
xtest = train_df['x_test']
ytest = train_df['y_test']
Y_predict, loss_array, it_count = model(xtest,ytest)

#plt.plot(xtest,ytest,'.')
#plt.plot(xtest, Y_predict, label='testing set')
plt.plot(it_count, loss_array, '.')
plt.title('testing data error')
plt.show()
print("We're making it to the end :D")
