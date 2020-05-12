#!/usr/bin/env python
# coding: utf-8

# ## HW3: Decision Tree and Random Forest
# In hw3, you need to implement decision tree and random forest by using only numpy, then train your implemented model by the provided dataset and test the performance with testing data
# 
# Please note that only **NUMPY** can be used to implement your model, you will get no points by simply calling sklearn.tree.DecisionTreeClassifier

import math
import statistics as st
import numpy as np
import pandas as pd
from sklearn.datasets import load_breast_cancer


data = load_breast_cancer()
feature_names = data['feature_names']
print(feature_names)

x_train = (pd.read_csv("x_train.csv"))
y_train = (pd.read_csv("y_train.csv"))
x_test = pd.read_csv("x_test.csv")
y_test = pd.read_csv("y_test.csv")

labels = []
# add the class label as an extra column for every row
training_data = np.column_stack((x_train, y_train))
x_train['label'] = y_train

# ## Question 1
# Gini Index or Entropy is often used for measuring the “best” splitting of the data. Please compute the Entropy and Gini Index of provided data. 
# Please use the formula from [page 7 of hw3 slides](https://docs.google.com/presentation/d/1ish3jEr_6be0FK4kgOZa12nYAyJFh0P2LCNsNPOCiXo/edit#slide=id.g7703d1636d_0_21)

# Maybe want to turn y_train into np.array beforehand?
def gini(sequence):
   
    sequence = np.array(sequence)
    #print(sequence[0,-1])
    c1 = sequence[sequence[:,-1] == 0]
    c2 = sequence[sequence[:,-1] == 1]

    impurity = (len(c1) / len(sequence)) ** 2 + (len(c2) / len(sequence)) ** 2

    return  1 - impurity 

def entropy(sequence):
    
    sequence = np.array(sequence)
    c1 = sequence[sequence[:,-1] == 0]
    c2 = sequence[sequence[:,-1] == 1]
    
    p1 = len(c1) / len(sequence) # probability of point being in class 1
    p2 = len(c2) / len(sequence) # probability of point being in class 2
    # print(f"p1: {p1} \t p2:{p2} ")

    ent = p1 * math.log(p1, 2) + p2 * math.log(p2, 2)
    return -ent


gini(training_data)
# 1 = class 1,
# 2 = class 2
data = np.array([1,2,1,1,1,1,2,2,1,1,2])



# print("Gini of data is ", gini(data))
# print("Entropy of data is ", entropy(data))


# ## Question 2
# Implement the Decision Tree algorithm (CART, Classification and Regression Trees) and trained the model by the given arguments, and print the accuracy score on the test data. 
# You should implement two arguments for the Decision Tree algorithm
# 1. **Criterion**: The function to measure the quality of a split. Your model should support “gini” for the Gini impurity and “entropy” for the information gain. 
# 2. **Max_depth**: The maximum depth of the tree. If Max_depth=None, then nodes are expanded until all leaves are pure. Max_depth=1 equals to split data once
# 

class DecisionTree():
    def __init__(self, criterion='gini', max_depth=None):
        self.criterion = criterion
        self.max_depth = max_depth
        self.count = 0 # count of how many iterations
        self.used = [] # names of used features
        self.tree(x_train)
        return None

    # maybe build the tree here?
    def tree(self, data):

        purity = gini(data) if self.criterion == 'gini' else entropy(data)
        # for all the features
        for i in feature_names:
            tmp = data[i]

            # the threshold for the partition will be the average 
            # value of the data field. Maybe some other way?
            threshold = st.mean(tmp)
            print(f"avg for {i}: {threshold}")
            less_than = []
            greater_than = []

            # partition the nodes if the value is lesser or greater
            for j in range(tmp.shape[0]):
                if tmp[j] < threshold:
                    less_than.append(data.iloc[j])
                else:
                     greater_than.append(data.iloc[j])
# ### Question 2.1
# Using Criterion=‘gini’, showing the accuracy score of test data by Max_depth=3 and Max_depth=10, respectively.
# 

clf_depth3 = DecisionTree(criterion='gini', max_depth=3)
clf_depth10 = DecisionTree(criterion='gini', max_depth=10)

clf_depth3.tree(x_train)
# ### Question 2.2
# Using Max_depth=3, showing the accuracy score of test data by Criterion=‘gini’ and Criterion=’entropy’, respectively.
# 


clf_gini = DecisionTree(criterion='gini', max_depth=3)
clf_entropy = DecisionTree(criterion='entropy', max_depth=3)


# - Note: All of your accuracy scores should over 0.9
# - Note: You should get the same results when re-building the model with the same arguments,  no need to prune the trees
# - Hint: You can use the recursive method to build the nodes
# 

# ## Question 3
# Plot the [feature importance](https://sefiks.com/2020/04/06/feature-importance-in-decision-trees/) of your Decision Tree model. You can get the feature importance by counting the feature used for splitting data.
# 
# - You can simply plot the feature counts for building tree without normalize the importance
# 
# ![image](https://i2.wp.com/sefiks.com/wp-content/uploads/2020/04/c45-fi-results.jpg?w=481&ssl=1)


# ## Question 4
# implement the Random Forest algorithm by using the CART you just implemented from question 2. You should implement two arguments for the Random Forest.
# 
# 1. **N_estimators**: The number of trees in the forest. 
# 2. **Max_features**: The number of random select features to consider when looking for the best split
# 3. **Bootstrap**: Whether bootstrap samples are used when building tree
# 




class RandomForest():
    def __init__(self, n_estimators, max_features, boostrap=True, criterion='gini', max_depth=None):
        return None


# ### Question 4.1
# Using Criterion=‘gini’, Max_depth=None, Max_features=sqrt(n_features), showing the accuracy score of test data by n_estimators=10 and n_estimators=100, respectively.
# 


clf_10tree = RandomForest(n_estimators=10, max_features=np.sqrt(x_train.shape[1]))
clf_100tree = RandomForest(n_estimators=100, max_features=np.sqrt(x_train.shape[1]))





# ### Question 4.2
# Using Criterion=‘gini’, Max_depth=None, N_estimators=10, showing the accuracy score of test data by Max_features=sqrt(n_features) and Max_features=n_features, respectively.
# 


clf_all_features = RandomForest(n_estimators=10, max_features=np.sqrt(x_train.shape[1]))
clf_random_features = RandomForest(n_estimators=10, max_features=x_train.shape[1])


# - Note: Use majority votes to get the final prediction, you may get slightly different results when re-building the random forest model





# ## Supplementary
# If you have trouble to implement this homework, TA strongly recommend watching [this video](https://www.youtube.com/watch?v=LDRbO9a6XPU), which explains Decision Tree model clearly. But don't copy code from any resources, try to finish this homework by yourself! 




