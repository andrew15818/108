#!/usr/bin/env python # coding: utf-8

# ## HW2: Linear Discriminant Analysis
# In hw2, you need to implement Fisher’s linear discriminant by using only numpy, then train your implemented model by the provided dataset and test the performance with testing data
# 
# Please note that only **NUMPY** can be used to implement your model, you will get no points by simply calling sklearn.discriminant_analysis.LinearDiscriminantAnalysis 

# ## Load data
import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score

### How many closest neighbors we check to make our prediction
K = 2

##get the index of the nearest neighbor to data[index]
##TODO: Maybe change this algo to not be O(n^2)
def get_nearest_neighbor(index, data):
    
    testing = data[index % len(data)] 
    tmp = data[0]
    best_index = 0
    min_dist = ( abs(tmp - data[1]) ) #initial min-distance
    for i in range(0, len(data)):
        """
        if i == index: #to avoid a zero minimum distance
            continue
        """
        tmp = data[i]
        curr_dist = math.sqrt(abs(tmp - testing))
        if(curr_dist < min_dist):
            min_dist = curr_dist
            best_index = i
    return best_index


#returns a list or some container with the class predictions 
def get_class_estimation(index, x_train):
    min_dist = np.absolute(x_train[index] - x_train[1])
    best_index = 0


    for i in range(0, len(x_train)):
        dist = np.absolute(x_train[index] - x_train[i])
        if(dist < min_dist):
            min_dist = dist
            best_index = i
    return i
x_train = pd.read_csv("x_train.csv").values
y_train = pd.read_csv("y_train.csv").values[:,0]
x_test = pd.read_csv("x_test.csv").values
y_test = pd.read_csv("y_test.csv").values[:,0]

print("x_train.shape: " + str(x_train.shape))
print("y_train.shape: " + str(y_train.shape))
print("x_test.shape: " + str(x_test.shape))
print("y_test.shape: " + str(y_test.shape))


# ## 1. Compute the mean vectors mi, (i=1,2) of each 2 classes
x_train = np.array(x_train)
#selecting the elements that belong to each class


c1 = x_train[y_train == 0] 
c2 = x_train[y_train == 1]
print(f"class1 shape: {c1.shape}", f"class2 shape{c2.shape}")

#getting the class means 
m1 = np.mean(c1, axis = 0)
m2 = np.mean(c2, axis = 0)

assert m1.shape == (2,)
#print("shape of m1:  " + str(m1.shape) +"\t shape of m2: " + str(m2.shape))
print(f"mean vector of class 1: {m1}", f"mean vector of class 2: {m2}")


# ## 2. Compute the Within-class scatter matrix SW

## Your code HERE
tmp = np.array

#the within-class variance is the difference bw actual value and class mean
#empty arrays
sw1 = 0
sw2 = 0 
for i in range(0, c1.shape[0]):
    tmp = (c1[i] - m1)[np.newaxis] #separate the two coluns so we can transpose the array
    sw1 += np.matmul(tmp.T, tmp)

for i in range(0, c2.shape[0]):
    tmp = (c2[i] - m2)[np.newaxis]   
    sw2 += np.matmul(tmp.T, tmp)#(tmp * tmp.T) <-igual aqui
sw = sw1 + sw2
assert sw.shape == (2,2)

print(f"Within-class scatter matrix SW: {sw}")


# ## 3.  Compute the Between-class scatter matrix SB
tmp = (m2 - m1)[np.newaxis]
sb = np.matmul(tmp.T, tmp)#(tmp * tmp.T)

assert sb.shape == (2,2)
print(f"Between-class scatter matrix SB: {sb}")


# ## 4. Compute the Fisher’s linear discriminant
## Your code HERE
"""
First, we have to calculate w, which is proportional to the within-class scatter matrix and the direction of the two means
then, we can quickly calculate J(w), which involves the within and between scatter matrices
"""
jw = ((m2 - m1) ** 2) / ((sw1)** 2 + sw2 ** 2)
#print("jw shapearooni: " + str(jw.shape))
print(f"Fisher's criterion: {jw}")

mean_diff = (m2 - m1)[:, np.newaxis]
sw_inv = np.linalg.inv(sw) 
w = np.matmul(sw_inv, mean_diff)
w *= 100
assert w.shape == (2,1)
print(f" Fisher’s linear discriminant: {w}")



# ## 5. Project the test data by linear discriminant to get the class prediction by nearest-neighbor rule and calculate the accuracy score 
# you can use accuracy_score function from sklearn.metric.accuracy_score
# this is projecting the training data?
print(f"shapes of w: {w.shape} and x_train: {x_train.shape}")

train_projection = np.matmul(x_train, w)
test_projection  = np.matmul(x_test, w)
projection_line = np.matmul(train_projection, w.T)
y_test_class_pred = np.zeros(test_projection.shape)

#For each point in testing set, calculate nearest point in training set
for i in range(0, test_projection.shape[0]):
    min_dist = np.absolute(test_projection[i] - train_projection[0]) # just placeholder min distance
    best_index = 0

    for j in range(0, train_projection.shape[0]):
        curr_dist = np.absolute( test_projection[i] - train_projection[j])

        if curr_dist < min_dist: #if we found a closer point in training data
            min_dist = curr_dist
            best_index = j  

    y_test_class_pred[i] = ( y_train[best_index])

#calculating the k-nearest neighbors
rise = projection_line[100]
run = projection_line[2]
slope =  (rise[1] - run[1]) / (rise[0] - run[0]) 

y_intercept =   rise[1] - (slope *rise[0])
print(f"rise : {rise} \t run: {run} \t slope {slope} \t y-intercept: {y_intercept}")
print(y_intercept)

print(f"slope: {slope}")
acc = accuracy_score(y_test, y_test_class_pred)

print(f"accuracy of y: {acc}")
color = []
for i in y_train:
    if i == 0:
        color.append("green")
    else:
        color.append("blue")

#Plotting the classes, and the two 
colors_train = ["green" if  l==0 else "orange" for l in y_train]
colors_test = ["green" if  l==0 else "orange" for l in y_test]
proj_line_c1 = projection_line[y_train == 1]
proj_line_c2 = projection_line[y_train == 0]

plt.plot(proj_line_c1[:,0], proj_line_c1[:,1],'.' ,color = "red")
plt.plot(proj_line_c2[:,0], proj_line_c2[:,1],'.' ,color = "green")

plt.plot(c1[:,0], c1[:,1],'+' ,color="green")
plt.plot(c2[:,0], c2[:,1],'+' ,color="red")
plt.title("slope: " + str(slope)) 
plt.show()
