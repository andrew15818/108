import numpy as np 
import pandas as pd
import time
from random import randrange
import matplotlib.pyplot as plt 

#constants
ITERATIONS = 1000
LEARNING_RATE = 1e-2
SLOPE_GRADIENT = 1
INT_GRADIENT = 2

#returns the estimated slope and intercepts 
def model(xtrain, ytrain):
    #values we try to maximize
    slope = 0
    intercept = 0 

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
 

    return Y_predict, slope, intercept 

#import the data from the csv, x and y values
train_df = pd.read_csv("train_data.csv")

#values we use estimate the values
slope = 0
intercept = 0

#Modeling and plotting the training data
xtrain = train_df['x_train']
ytrain = train_df['y_train']
Y_predict, slope, intercept = model(xtrain,ytrain)
plt.plot(xtrain, ytrain, '.') #original test points
plt.plot(xtrain, Y_predict) #our estimate for the line
plt.title('estimate for the training data')

error = np.square(np.subtract(ytrain, Y_predict)).mean()
print('Training data info: \n')
print('slope: ' + str(slope) + '\tintercept: ' + str(intercept) + '\terror: '+str(error))
plt.show()




#handling the test data
train_df = pd.read_csv("test_data.csv")
xtest = train_df['x_test']
ytest = train_df['y_test']
Y_predict = xtest * slope + intercept
error = np.square(np.subtract(ytest, Y_predict)).mean()
print('\nTesting data info:\n')
print('slope: ' + str(slope) + '\tintercept: ' + str(intercept) + '\terror: '+str(error))



#create the final plot

plt.plot(xtest,ytest,'.') #testing points
plt.plot(xtest, Y_predict, label='testing set') #estimating line
plt.title('estimation for the testing data')
plt.show()
