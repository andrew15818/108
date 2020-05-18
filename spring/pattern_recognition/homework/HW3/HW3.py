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
from sklearn.metrics import accuracy_score
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
def gini_sequence(sequence):
    c1 = len([i for i in sequence if i == 1])
    c2 = len([i for i in sequence if i == 2])

    p1 = c1 / len(sequence)
    p2 = c2 / len(sequence)

    return 1 - (p1 ** 2) - (p2 ** 2)


def entropy_sequence(sequence):
    c1 = len([i for i in sequence if i == 1])
    c2 = len([i for i in sequence if i == 2])

    p1 = c1 / len(sequence)
    p2 = c2 / len(sequence)

    ent = p1 * math.log(p1, 2) + p2 * math.log(p2, 2)
    return -ent

# Maybe want to turn y_train into np.array beforehand?
def gini(sequence):
   
    #sequence = np.array(sequence)
    #print(sequence[0,-1])
    c1 = len(sequence['label'] == 0)
    c2 = len(sequence['label'] == 1)


    # if either one is empty, return maximum mixing value
    if c1 == 0 or c2 == 0:
        return 1

    impurity = (c1 / (c1 + c2) ) ** 2 + (c2 / (c1 + c2)) ** 2

    return  1 - impurity 

print(gini(x_train))
def entropy(sequence):
    
    sequence = np.array(sequence)
    c1 = sequence[sequence[:,-1] == 0]
    c2 = sequence[sequence[:,-1] == 1]
    
    p1 = len(c1) / len(sequence) # probability of point being in class 1
    p2 = len(c2) / len(sequence) # probability of point being in class 2
    # print(f"p1: {p1} \t p2:{p2} ")

    ent = p1 * math.log(p1, 2) + p2 * math.log(p2, 2)
    return -ent



# 1 = class 1,
# 2 = class 2

data = np.array([1,2,1,1,1,1,2,2,1,1,2])
# print(f"gini of sample data: {gini_sequence(data)} and entropy: {entropy_sequence(data)}")


# print("Gini of data is ", gini(data))
# print("Entropy of data is ", entropy(data))


# ## Question 2
# Implement the Decision Tree algorithm (CART, Classification and Regression Trees) and trained the model by the given arguments, and print the accuracy score on the test data. 
# You should implement two arguments for the Decision Tree algorithm
# 1. **Criterion**: The function to measure the quality of a split. Your model should support “gini” for the Gini impurity and “entropy” for the information gain. 
# 2. **Max_depth**: The maximum depth of the tree. If Max_depth=None, then nodes are expanded until all leaves are pure. Max_depth=1 equals to split data once
# 
class Node():
    def __init__(self,):
        self.right = None
        self.left = None
        self.threshold = 0
        self.feature = ""
        # self.data = data

        # use these two when doing the actual classification
        self.label = None
        self.is_leaf = False
        self.count = 0 # distance from the root node

class DecisionTree():
    def __init__(self, criterion='gini', max_depth=None):

        self.criterion = criterion
        self.max_depth = max_depth
        # self.count = 0 # count of how many iterations
        self.used = [] # names of used features
        self.root = Node()
        self.root = self.tree(x_train, self.root)


    def print_tree_helper(self, node):
        if node == None:
            return
        elif node.is_leaf == True:
            print(f"\treached label node with label: {node.label}")
            return
        print(f"feature name: {node.feature}\t feature threshold: {node.threshold}")
        self.print_tree_helper(node.left)
        
        self.print_tree_helper(node.right)

    def  print_tree(self):
        if self.root == None:
            print("root is None!")
        
        self.print_tree_helper(self.root)

    # just to avoid having an if-else every time we want the purity
    def purity(self, data):
        if data.shape[0] == 0:
            return 0
        return gini(data) if self.criterion == 'gini' else entropy(data)

    # get the purity of the split using this feature, weight it using the number of elements
    def split_purity(self, feature_column, threshold, data):
        # purity for values lower than thresh
        c1 = sum((feature_column <= threshold ) & (data['label'] == 0))
        c2 = sum((feature_column <= threshold) &(data['label'] == 1))
        tmp = (c1 / (c1 + c2)) ** 2 + (c2 /  (c1 + c2) ) ** 2 if (c1 + c2 != 0) else 0
        tmp *= ((c1 + c2) / (data.shape[0]))

        # purity for splitting values greater than thresh 
        c3 = sum((feature_column > threshold ) & (data['label'] == 0))
        c4 = sum((feature_column > threshold ) & (data['label'] == 1))
        tmp2 = (c3 / (c3 + c4)) ** 2 + (c4 / (c3 + c4)) ** 2 if (c3 + c4 != 0) else 0
        tmp2 *= ((c3 + c4) / (data.shape[0]))

        return 1 - tmp - tmp2

    def best_split_on_feature(self, feature, feature_column, data):

        best_thresh = None 
        best_purity = 10000
        best_left = None
        best_right = None

        #checking if every value in a given column splits the dataset better

        for i in feature_column: #range(feature_column.shape[0]):

            right = []
            # curr_thresh = feature_column[i] 
            curr_thresh = i 


            curr_purity = self.split_purity(feature_column, curr_thresh, data)

            # if split leads to lower impurity, do the split to save time
            if curr_purity < best_purity:

                #best_left = [data.iloc[row] for row in range(0, feature_column.shape[0]) if feature_column[row] <= curr_thresh]
                #best_right = [data.iloc[row] for row in range(0, feature_column.shape[0]) if feature_column[row] > curr_thresh]
                best_left = data[data[feature] <= curr_thresh]
                best_right = data[data[feature] > curr_thresh]
                best_thresh = curr_thresh
                best_purity = curr_purity
        
        #best_left = pd.DataFrame(best_left, columns=data.columns)
        #best_right = pd.DataFrame(best_right, columns=data.columns)

        return best_purity, best_thresh, best_right, best_left

    # maybe build the tree here?
    def tree(self, data, parent):
        curr_node = Node() 
        curr_node.count =  parent.count + 1
        print(f"node at depth: {curr_node.count}")

        # if reached the depth limit, add a node based on which class has most nodes in data 
        if curr_node.count > self.max_depth:
            class1_count = len([ i for i in data['label'] if i == 0])
            class2_count = len([i for i in data['label'] if i == 1])

            print(f"\t\tReached the count limit: {class1_count}, {class2_count}")
            curr_node.label = 0 if class1_count >= class2_count else 1
            curr_node.is_leaf = True 
            return curr_node

        elif data.shape[0] == 0:
            return None


        purity = gini(data) if self.criterion == 'gini' else entropy(data)
        print(f"\tdata shape : {data.shape} purity: {purity}")

        #all nodes belong to onlly one class
        if purity == 0:
            curr_node.is_leaf = True
            curr_node.label = data['label'].iloc[0] # since all nodes are from same class, assign the first data label
            print(f" \tlabel once we reach the end of the node:{ curr_node.label}")
            print('\tpurity is 0, returning')
            return  curr_node
        
        best_feature = " "
        best_purity = 100000
        less_count = 0
        great_count = 0
        best_less_than = pd.DataFrame(columns=x_train.columns)
        best_greater_than = pd.DataFrame(columns=x_train.columns)

        # for all the features
        for i in feature_names:
            # current feature we are comparing
            datarow = data[i]
            tmp_purity, threshold, less_than, greater_than = self.best_split_on_feature(i, datarow, data)



            # checking for value with best purity
            if tmp_purity <= best_purity: 
                best_purity = tmp_purity
                best_threshold = threshold
                best_feature = i
                best_less_than = less_than # make sure these values are actually the ones we want to assign
                best_greater_than = greater_than


        curr_node.feature = best_feature
        curr_node.threshold = best_threshold
        curr_node.count = parent.count + 1

        print(f"\tbest feature is : {best_feature} with threshold: {best_threshold}")
        print(f"\tbest_less_than shape: {best_less_than.shape} best_greater_than shape: {best_greater_than.shape}") 

        # recurse on the children
        curr_node.right = self.tree(best_greater_than, curr_node)
        curr_node.left = self.tree(best_less_than, curr_node) 
        return curr_node

    # recurse through the tree 
    def classify_node(self, node, data):
        # stop the recursion
        if node.is_leaf == True:   

            return node.label

        feature = node.feature

        # recurse on children node
        if data[feature] <= node.threshold:
            return self.classify_node(node.left, data)

        elif data[feature] > node.threshold:
            return self.classify_node(node.right, data)

    # classify all the nodes in the test sequence
    def classify(self, data):
        print(f"roots' feature: {self.root.feature}")
        classification = []

        # classify the nodes individually
        for i in range(data.shape[0]):
            tmp = data.loc[i] 

            classification.append( self.classify_node(self.root, tmp) )

        return classification

       
        
# ### Question 2.1
# Using Criterion=‘gini’, showing the accuracy score of test data by Max_depth=3 and Max_depth=10, respectively.
# 
# testo = DecisionTree(criterion='gini', max_depth=None)
clf_depth3 = DecisionTree(criterion='gini', max_depth=3)
class_predictions = clf_depth3.classify(x_test)
print(f"accuracy: {accuracy_score(y_test, class_predictions)}")
clf_depth3.print_tree()
#clf_depth10 = DecisionTree(criterion='gini', max_depth=10)


# ### Question 2.2
# Using Max_depth=3, showing the accuracy score of test data by Criterion=‘gini’ and Criterion=’entropy’, respectively.
# 


#clf_gini = DecisionTree(criterion='gini', max_depth=3)
#clf_entropy = DecisionTree(criterion='entropy', max_depth=3)


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




