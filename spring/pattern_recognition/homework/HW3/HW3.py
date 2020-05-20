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
from random import randrange
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
    c1 = sum(sequence == 1)
    c2 = sum(sequence == 2)
 
    p1 = c1 / len(sequence)
    p2 = c2 / len(sequence)

    ent = p1 * math.log(p1, 2) + p2 * math.log(p2, 2)
    return -ent

# Maybe want to turn y_train into np.array beforehand?
def gini(sequence):
   
    #sequence = np.array(sequence)
    #print(sequence[0,-1])
    c1 = sum(sequence['label'] == 0)
    c2 = sum(sequence['label'] == 1)


    # if either one is empty, return maximum mixing value
    if c1 == 0 or c2 == 0:
        return 0

    impurity = (c1 / (c1 + c2) ) ** 2 + (c2 / (c1 + c2)) ** 2

    return  1 - impurity 


def entropy(sequence):
    
    sequence = np.array(sequence)
    c1 = sequence[sequence[:,-1] == 0]
    c2 = sequence[sequence[:,-1] == 1]
    
    p1 = len(c1) / len(sequence) # probability of point being in class 1
    p2 = len(c2) / len(sequence) # probability of point being in class 2
    # print(f"p1: {p1} \t p2:{p2} ")
    ent1 = p1 * math.log(p1, 2) if p1 != 0 else 0
    ent2 = p2 * math.log(p2, 2) if p2 != 0 else 0

    ent =  ent1 + ent2
    return -ent



# 1 = class 1,
# 2 = class 2

data = np.array([1,2,1,1,1,1,2,2,1,1,2])
print(f"gini of sample data: {gini_sequence(data)} and entropy: {entropy_sequence(data)}")


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
    def __init__(self, criterion='gini', max_depth=None, features_list=feature_names):

        self.criterion = criterion
        self.max_depth = max_depth
        # self.count = 0 # count of how many iterations
        self.features_list = features_list
        self.root = Node()
        self.root = self.tree(x_train, self.root)


    def print_tree_helper(self, node):
        if node == None:
            return
        elif node.is_leaf == True:
            #print(f"\treached label node with label: {node.label}")
            return
        #print(f"feature name: {node.feature}\t feature threshold: {node.threshold}")
        self.print_tree_helper(node.left)
        
        self.print_tree_helper(node.right)

    def  print_tree(self):
        if self.root == None:
            print("root is None!")
        
        self.print_tree_helper(self.root)


    # get the purity of the split using this feature, weight it using the number of elements
    # it's more efficient to use it only with the 
    def split_purity(self, feature_column, threshold, data):
        # purity for values lower than thresh
        c1 = sum((feature_column <= threshold ) & (data['label'] == 0))
        c2 = sum((feature_column <= threshold) &(data['label'] == 1))
        p1 = c1 / (c1 + c2) if (c1 + c2 != 0) else 0
        p2 = c2 / (c1 + c2) if (c1 + c2 != 0) else 0

        # purity for splitting values greater than thresh 
        c3 = sum((feature_column > threshold ) & (data['label'] == 0))
        c4 = sum((feature_column > threshold ) & (data['label'] == 1)) 
        p3 = c3 / (c3 + c4) if (c3 + c4 != 0) else 0
        p4 = c4 / (c3 + c4) if (c3 + c4 != 0) else 0

        # applying the gini and entropy formulas for both branches of split
        if self.criterion == 'entropy':
            try:
                tmp = -((p1 * math.log(p1, 2)) + (p2 * math.log(p2, 2)))
            except:
                tmp = 0
            try:
                tmp2 = -((p3 * math.log(p3, 2)) + (p4 * math.log(p4, 2)))
            except:
                tmp2 = 0

        else:
            tmp = p1 ** 2 + p2 ** 2 
            tmp2 = p3 ** 2 + p4 ** 2 

        # to get the weighted value
        tmp *= ((c1 + c2) / (data.shape[0]))
        tmp2 *= ((c3 + c4) / (data.shape[0]))

        # return the value according to the criterion
        return 1 - tmp - tmp2 if self.criterion == 'gini' else tmp + tmp2

    def best_split_on_feature(self, feature, feature_column, data):

        best_thresh = None 
        best_purity = 10000
        best_left = None
        best_right = None

        #checking if every value in a given column splits the dataset better
        for i in feature_column: 

            curr_thresh = i 

            curr_purity = self.split_purity(feature_column, curr_thresh, data)

            # if split leads to lower impurity, do the split to save time
            if curr_purity < best_purity: 
                best_left = data[data[feature] <= curr_thresh]
                best_right = data[data[feature] > curr_thresh]
                best_thresh = curr_thresh
                best_purity = curr_purity
        
        return best_purity, best_thresh, best_right, best_left

    # maybe build the tree here?
    def tree(self, data, parent):
        curr_node = Node() 
        curr_node.count =  parent.count + 1
        #print(f"node at depth: {curr_node.count}")

        # if reached the depth limit, add a node based on which class has most nodes in data 
        try:
            if curr_node.count > self.max_depth:
                class1_count = sum(data['label'] == 0)
                class2_count = sum(data['label'] == 1)

                # print(f"\t\tReached the count limit: {class1_count}, {class2_count}")

                curr_node.label = 0 if class1_count >= class2_count else 1
                curr_node.is_leaf = True 
                # print(f"\t\tthis node's label is : {curr_node.label}")
                return curr_node
        except:
            pass


        if data.shape[0] == 0:
            return None


        purity = gini(data) if self.criterion == 'gini' else entropy(data)


        #all nodes belong to onlly one class
        if purity == 0:
            curr_node.is_leaf = True
            curr_node.label = data['label'].iloc[0] # since all nodes are from same class, assign the first data label
            #print(f" \tlabel once we reach the end of the node:{ curr_node.label}")
            # print('\tpurity is 0, returning')
            return  curr_node
        
        best_feature = " "
        best_purity = 100000
        less_count = 0
        great_count = 0
        best_less_than = pd.DataFrame(columns=x_train.columns)
        best_greater_than = pd.DataFrame(columns=x_train.columns)

        # for all the features
        for i in self.features_list:
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

        #print(f"\tbest feature is : {best_feature} with threshold: {best_threshold}")
        #print(f"\tbest_less_than shape: {best_less_than.shape} best_greater_than shape: {best_greater_than.shape}") 

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
            return self.classify_node(node.right, data)

        elif data[feature] > node.threshold:
            return self.classify_node(node.left, data)

    # classify all the nodes in the test sequence individually
    def classify(self, data): 
        classification = []

        # classify the nodes individually
        for i in range(data.shape[0]):
            tmp = data.loc[i] 

            classification.append( self.classify_node(self.root, tmp) )

        return classification

       
        
# ### Question 2.1
# Using Criterion=‘gini’, showing the accuracy score of test data by Max_depth=3 and Max_depth=10, respectively.
# 


clf_depth3 = DecisionTree(criterion='gini', max_depth=3)
class_predictions = clf_depth3.classify(x_train)
print(f"accuracy clf_depth3: {accuracy_score(y_train, class_predictions)}")

clf_depth10 = DecisionTree(criterion='gini', max_depth=10)
class_predictions = clf_depth10.classify(x_train)
print(f"accuracy clf_depth10: {accuracy_score(y_train, class_predictions)}")

# ### Question 2.2
# Using Max_depth=3, showing the accuracy score of test data by Criterion=‘gini’ and Criterion=’entropy’, respectively.
# 

clf_gini = DecisionTree(criterion='gini', max_depth=3)
class_predictions = clf_gini.classify(x_test)
print(f"accuracy clf_gini: {accuracy_score(y_test, class_predictions)}")


clf_entropy = DecisionTree(criterion='entropy', max_depth=3)
class_predictions = clf_entropy.classify(x_test)
print(f"accuracy clf_entropy: {accuracy_score(y_test, class_predictions)}")

# - Note: All of your accuracy scores should over 0.9
# - Note: You should get the same results when re-building the model with the same arguments,  no need to prune the trees
# - Hint: You can use the recursive method to build the nodes
# 

# ## Question 3
# Plot the [feature importance](https://sefiks.com/2020/04/06/feature-importance-in-decision-trees/ ) of your Decision Tree model. You can get the feature importance by counting the feature used for splitting data.
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


feature_names_orig = feature_names.copy()

class RandomForest():
    def __init__(self, n_estimators, max_features=None, bootstrap=True, criterion='gini', max_depth=None):
        self.n_estimators = n_estimators      # how many trees to use
        self.max_features = int(max_features) # number of features to randomly sample, rounded down to nearest integer
        self.bootsrap = bootstrap             # whether to use bootstrapped samples 
        self.criterion = criterion            # which function to use as purity check
        self.max_depth = max_depth            # how many layers our tree can have
        self.features = []                    # set of features we will use
        self.predictions = []
        
        print(f"Building random forest with: n_estimators{self.n_estimators} \
                max_features:{self.max_features} criterion: {self.criterion}")

        return None
    def gen_features_list(self):
        i = 0

        # choosing an index from features matrix to insert in our list 
        # Since features in the tree can be repeated in the tree construction,
        # we don't allow repetition when selecting the features here
        while i < self.max_features:
            index = randrange(len(feature_names_orig))
            if feature_names_orig[index] in self.features:
                continue

            self.features.append(feature_names_orig[index])
            i += 1
    def majority_vote(self, predictions):
        # if half or more of the  trees classified it 
        # as certain class, leave it like that
        class_threshold = int(self.n_estimators / 2)        

        for i in range(len(predictions)):
            self.predictions[i] = 1 if self.predictions[i] > class_threshold else 0

    def update_predictions(self, predictions, curr_predictions):  
        # update the count in our total predictions list
        for index, i in enumerate(curr_predictions):
            if i == 1:
                self.predictions[index] += 1

    def get_predictions(self):
        return self.predictions 

    def build_forest(self, data):
        # overall class predictions with given size
        self.predictions = [0] * data.shape[0]    


        for i in range(self.n_estimators):

             # generate the features we use for this tree
            self.gen_features_list()
            # check the PEP8 formatting here
            dec_tree = DecisionTree(
                criterion=self.criterion, 
                max_depth=self.max_depth, 
                features_list=self.features)

            # class labels for the current tree 
            curr_predictions = dec_tree.classify(data)
            self.update_predictions(self.predictions, curr_predictions)
            #print(predictions)

        # get the final classifications 
        self.majority_vote(self.predictions)




# ### Question 4.1
# Using Criterion=‘gini’, Max_depth=None, Max_features=sqrt(n_features), showing the accuracy score of test data by n_estimators=10 and n_estimators=100, respectively.
# 

clf_10tree = RandomForest(n_estimators=10, max_features=np.sqrt(x_train.shape[1]))
clf_10tree.build_forest(x_train)
print(f"clf10tree accuracy: \
    {accuracy_score(y_train, clf_10tree.get_predictions())}")

clf_100tree = RandomForest(n_estimators=100, max_features=np.sqrt(x_train.shape[1]))
clf_100tree.build_forest(x_train)
print(f"clf_100tree accuracy: \
    {accuracy_score(y_train, clf_10tree.get_predictions())}")

# ### Question 4.2
# Using Criterion=‘gini’, Max_depth=None, N_estimators=10, showing the accuracy score of test data by Max_features=sqrt(n_features) and Max_features=n_features, respectively.
# 


clf_all_features = RandomForest(n_estimators=10, max_features=np.sqrt(x_train.shape[1]))
clf_all_features.classify(x_test)
print(f"clf_all_features accuracy: \
    {accuracy_score(y_test, clf_all_features.get_predictions())}")

clf_random_features = RandomForest(n_estimators=10, max_features=x_train.shape[1])
clf_random_features.classify(x_test)
print(f"clf_random_features accuracy: \
    {accuracy_score(y_test, clf_random_features.get_predictions())}")
# - Note: Use majority votes to get the final prediction, you may get slightly different results when re-building the random forest model

# ## Supplementary
# If you have trouble to implement this homework, TA strongly recommend watching [this video](https://www.youtube.com/watch?v=LDRbO9a6XPU), which explains Decision Tree model clearly. But don't copy code from any resources, try to finish this homework by yourself! 
