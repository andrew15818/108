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

x_train = pd.read_csv("x_train.csv")
y_train = pd.read_csv("y_train.csv")
x_test = pd.read_csv("x_test.csv")
y_test = pd.read_csv("y_test.csv")

# easier to split the dataset and calculate purity with the labels
x_train['label'] = y_train
print(x_train['label'])
# ## Question 1
# Gini Index or Entropy is often used for measuring the “best” splitting of the data. Please compute the Entropy and Gini Index of provided data. Please use the formula from [page 7 of hw3 slides](https://docs.google.com/presentation/d/1ish3jEr_6be0FK4kgOZa12nYAyJFh0P2LCNsNPOCiXo/edit#slide=id.g7703d1636d_0_21)


def gini(sequence):
    sequence =  np.array(sequence)
    # getting the members that belong to either class
    c1 = len(sequence[sequence == 1])
    c2 = len(sequence[sequence != 1 ])

    # probability of choosing a member in a given class
    p1 = c1 / (c1 + c2)
    p2 = c2 / (c1 + c2)
    return (1 - p1 ** 2 - p2 ** 2)


def entropy(sequence):
    sequence = np.array(sequence)
    # getting the members of each class
    c1 = len(sequence[sequence == 1])
    c2 = len(sequence[sequence != 1 ])

    # getting the prob. of choosing member of given class
    p1 = c1 / (c1 + c2)
    p2 = c2 / (c1 + c2)
    ent = p1 * math.log(p1, 2) + p2 * math.log(p2, 2)
    return -ent 


# 1 = class 1,
# 2 = class 2
data = np.array([1,2,1,1,1,1,2,2,1,1,2])



print("Gini of data is ", gini(data))
print("Entropy of data is ", entropy(data))


# ## Question 2
# Implement the Decision Tree algorithm (CART, Classification and Regression Trees) and trained the model by the given arguments, and print the accuracy score on the test data. You should implement two arguments for the Decision Tree algorithm
# 1. **Criterion**: The function to measure the quality of a split. Your model should support “gini” for the Gini impurity and “entropy” for the information gain. 
# 2. **Max_depth**: The maximum depth of the tree. If Max_depth=None, then nodes are expanded until all leaves are pure. Max_depth=1 equals to split data once
# 

class Node():
    def __init__(self):
        self.right = None
        self.left = None
        self.threshold = None
        self. purity = None
        self.feature = ""
        self.depth = -1
        self.is_leaf = False
        self.label = None
        self.purity = None


class DecisionTree():
    def __init__(self, criterion='gini', max_depth=None):
        self.criterion = criterion
        self.max_depth = max_depth
        self.root = Node()
        print(x_train['label'])
        self.build_tree(self.root, x_train)
        return None

    # return two lists with values gerater and smaller than threshold
    def split_data(self, feature, threshold, data):
        less_than = pd.DataFrame(columns=data.columns)
        greater_than = pd.DataFrame(columns=data.columns)
        less_count = 0
        great_count = 0
        # less_than = []
        #greater_than = []
        # just separate the data based on the threshold
        for row in range(data.shape[0]):
            
                if data[feature].iloc[row] < threshold:
                    less_than.loc[less_count] = data.iloc[row]             
                    # less_than.append(dict(row=less_count, info=data.iloc[row]))
                    less_count += 1
                else:
                   #  greater_than.append(dict(row=great_count, info=data.iloc[row]))
                    greater_than.loc[great_count] = data.iloc[row]
                    great_count += 1

        less_than = pd.DataFrame(less_than, columns=data.columns)
        greater_than = pd.DataFrame(greater_than, columns=data.columns)

        return less_than, greater_than 

    def get_best_threshold(self, node, data):

        best_threshold = 10000
        best_feature = ""
        best_purity  = 10000
        for feature_name in feature_names:

            # getting the column of values for that feature
            feature_values = list(data[feature_name])
            # feature_values.sort()

            #splitting according to the best feature value
            for value in range(1, len(feature_values)):
                if feature_values[value - 1] == feature_values[value]:
                    continue

                curr_threshold  = (feature_values[value - 1] + feature_values[value]) / 2
                less_than, greater_than = self.split_data(feature_name, curr_threshold, data)
                purity = gini(less_than['label']) + gini(greater_than['label'])
                if purity < best_purity:
                    print(f"found better purity:{purity} with threshold: {curr_threshold}")
                    best_purity = purity
                    best_feature = feature_name
                    best_threshold = curr_threshold
        print(best_feature)



    # need the parent to calculate the height for the child node
    def build_tree(self, parent, data):
        curr_node = Node()
        curr_node.depth = parent.depth + 1

        purity = gini(data['label']) if self.criterion == "gini" else entropy(data['label'])

        # if all the nodes belong to the same class
        if purity == 0:
            curr_node.is_leaf = True
            curr_node.label = data['label'].iloc[0] # just assign label of first node

        curr_node.thresh = self.get_best_threshold(curr_node, data)
        print("Found the best thresh :D")

        

# ### Question 2.1
# Using Criterion=‘gini’, showing the accuracy score of test data by Max_depth=3 and Max_depth=10, respectively.
# 


clf_depth3 = DecisionTree(criterion='gini', max_depth=3)
clf_depth10 = DecisionTree(criterion='gini', max_depth=10)


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



