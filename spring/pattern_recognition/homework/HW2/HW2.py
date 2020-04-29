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

##get the index of the nearest neighbor to data[index]
##TODO: Maybe change this algo to not be O(n^2)
def get_nearest_neighbor(index, data):
    testing = data[index % len(data)] 
    tmp = data[0]
    best_index = 0
    min_dist = math.sqrt((tmp[0] - testing[0]) ** 2 + (tmp[1] - testing[1]) ** 2)

    for i in range(0, len(data)):
        if i == index:
            continue
        tmp = data[i]
        curr_dist = math.sqrt((tmp[0] - testing[0]) ** 2 + (tmp[1] - testing[1]) ** 2)
        if(curr_dist < min_dist):
            min_dist = curr_dist
            best_index = i
    
    return best_index


#returns a list or some container with the class predictions 
def get_class_estimations(x_train):
    #x_copy = list(x_train)
    y_class_pred = []

    for i in range(0, x_train.shape[0]): #for all points
        x_copy = list(x_train)
        c1count = 0
        c2count = 0
        visited_indices = []
        for j in range(0, K):           #do K neighbors
            closest = get_nearest_neighbor(i, x_copy)
            x_copy.pop(closest) 
            #print(f"\t\tRemoving {closest} from x_copy")
            if y_train[closest] == 0:
                c1count += 1
            else:
                c2count += 1
        if(c1count > c2count):
            y_class_pred.append(0)
        else:
            y_class_pred.append(1)
    return y_class_pred

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

assert w.shape == (2,1)
print(f" Fisher’s linear discriminant: {w}")



# ## 5. Project the test data by linear discriminant to get the class prediction by nearest-neighbor rule and calculate the accuracy score 
# you can use accuracy_score function from sklearn.metric.accuracy_score
# this is projecting the training data?
print(f"shapes of w: {w.shape} and x_train: {x_train.shape}")
y_pred = np.matmul(x_train, w)

y_class_pred = []

#calculating the k-nearest neighbors
#calculate the nearest neighbors for all the points
x_copy = (x_train)
y_class_pred = get_class_estimations(x_train)

acc = accuracy_score(y_train, y_class_pred)

print(f"accuracy of y: {acc}")

color = ['red' if l == 0 else "green" for l in y_class_pred]

plt.scatter(np.ones((y_pred.shape)), y_pred[:,0], color=color) #plotting the two classes
plt.plot(w)
plt.show()
