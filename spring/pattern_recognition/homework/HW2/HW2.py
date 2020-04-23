#!/usr/bin/env python
# coding: utf-8

# ## HW2: Linear Discriminant Analysis
# In hw2, you need to implement Fisher’s linear discriminant by using only numpy, then train your implemented model by the provided dataset and test the performance with testing data
# 
# Please note that only **NUMPY** can be used to implement your model, you will get no points by simply calling sklearn.discriminant_analysis.LinearDiscriminantAnalysis 

# ## Load data
import pandas as pd
import numpy as np

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

#getting the class means
m1 = np.mean(c1, axis = 0)
m2 = np.mean(c2, axis = 0)

assert m1.shape == (2,)
print(f"mean vector of class 1: {m1}", f"mean vector of class 2: {m2}")


# ## 2. Compute the Within-class scatter matrix SW

## Your code HERE
tmp = np.array

#the within-class variance is the difference bw actual value and class mean
s1 = (c1 - m1) ** 2
s2 = (c2 - m2) ** 2

s1 = np.sum(s1, axis = 0)
s2 = np.sum(s2, axis = 0)

sw = np.vstack((s1,s2))
assert sw.shape == (2,2)
print(f"Within-class scatter matrix SW: {sw}")


# ## 3.  Compute the Between-class scatter matrix SB

## Your code HERE
sb = (m2 - m1) ** 2
assert sb.shape == (2,2)
print(f"Between-class scatter matrix SB: {sb}")


# ## 4. Compute the Fisher’s linear discriminant

## Your code HERE


assert w.shape == (2,1)
print(f" Fisher’s linear discriminant: {w}")



# ## 5. Project the test data by linear discriminant to get the class prediction by nearest-neighbor rule and calculate the accuracy score 
# you can use accuracy_score function from sklearn.metric.accuracy_score

acc = accuracy(y_test, y_pred)

print(f"Accuracy of test-set {acc}")


# ## 6. Plot the 1) projection line 2) Decision boundary and colorize the data with each class
# ### the result should be look like this [image](https://i2.kknews.cc/SIG=fe79fb/26q1000on37o7874879n.jpg) (Red line: projection line, Green line: Decision boundary)

