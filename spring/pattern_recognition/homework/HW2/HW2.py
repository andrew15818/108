#!/usr/bin/env python
# coding: utf-8

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
K = 1

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
print("shape of m1:  " + str(m1.shape) +"\t shape of m2: " + str(m2.shape))
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
    sw1 += (tmp * tmp.T)

for i in range(0, c2.shape[0]):
    tmp = (c2[i] - m2)[np.newaxis]   
    sw2 += (tmp * tmp.T)
sw = sw1 + sw2
assert sw.shape == (2,2)

print(f"Within-class scatter matrix SW: {sw}")


# ## 3.  Compute the Between-class scatter matrix SB
tmp = (m2 - m1)[np.newaxis]
sb = (tmp * tmp.T)
assert sb.shape == (2,2)
print(f"Between-class scatter matrix SB: {sb}")


# ## 4. Compute the Fisher’s linear discriminant
## Your code HERE
"""
First, we have to calculate w, which is proportional to the within-class scatter matrix and the direction of the two means
then, we can quickly calculate J(w), which involves the within and between scatter matrices
"""
jw = ((m2 - m1) ** 2) / (sw1 ** 2 + sw2 ** 2)
print("jw shapearooni: " + str(jw.shape))
print(f"Fisher's criterion: {jw}")

mean_diff = (m2 - m1)[:,np.newaxis]
sw_inv = np.linalg.inv(sw) 
w = ( sw_inv * mean_diff)
w = (np.sum(w, axis = 1))[:, np.newaxis]
print(w.shape)
assert w.shape == (2,1)
print(f" Fisher’s linear discriminant: {w}")



# ## 5. Project the test data by linear discriminant to get the class prediction by nearest-neighbor rule and calculate the accuracy score 
# you can use accuracy_score function from sklearn.metric.accuracy_score
# this is projecting the training data?
y_pred = w.T * x_train 
y_class_pred = []

#calculating the k-nearest neighbors

min_distance_index = 0
distance = 0
#calculating closest point for every data in x
for i in range(0, x_train.shape[0]):
    current = x_train[i]
    min_distance = 10000
    #finding its closest point along all the adjacent ones 
    for j in range(0, x_train.shape[0]):
        if i == j:
            continue
        testing = x_train[j]  
        distance =  math.sqrt((current[0] - testing[0]) ** 2 + (current[1] - testing[1]) ** 2)
        if distance < min_distance:
            min_distance = distance
            min_distance_index = j
    #assigning a class prediction for our testing input based on closest data point
    if(y_train[min_distance_index] == 1):
        y_class_pred.append(1)
    else:
        y_class_pred.append(0)
y_class_pred = np.array(y_class_pred)
print("y_class_pred.shape = \t" + str(y_class_pred.shape))
#For the accuracy, we want to have a prediction matrix with either 0 or 1 for our test data.
acc = accuracy_score(y_train, y_class_pred)
#acc = accuracy_score(y_test, y_pred)
print(f"Accuracy of test-set {acc}")


# ## 6. Plot the 1) projection line 2) Decision boundary and colorize the data with each class
# ### the result should be look like this [image](https://i2.kknews.cc/SIG=fe79fb/26q1000on37o7874879n.jpg) (Red line: projection line, Green line: Decision boundary)

plt.plot(y_pred[y_class_pred == 0], '.', color="red")
plt.plot(x_train[y_train == 0], '.', color="blue")
plt.plot(x_train[y_train == 1], '.', color = "green")
#plt.plot(y_pred[y_class_pred == 1], '.', color="blue")
plt.plot(jw, '.',color="green")
plt.show()
