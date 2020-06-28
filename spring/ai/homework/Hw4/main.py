import numpy as np 
import pandas as pd 
from sklearn.model_selection import train_test_split
# Load the dataset
x_data = pd.read_csv("iris.data")

attributes = ["sepal length", "sepal width", 
                "petal length", "petal width"]

classes = x_data["class"].unique()

print(classes)
class Node:
    def __init__(self):
        feature_name = ""
        threshold = 0
        # Children
        right = None
        Left = None

print(f"Elements in the dataset: {len(x_data)}")

# Splitting the datasets into training and validation
x_train, x_test, y_train, y_test = train_test_split(x_data, x_data["class"], test_size=0.2)

# Get the Gini impurity by seeing how many elements are in each set
def Gini(dataset):
    if len(dataset) == 0:
        return 1

    class_prob = 0
    for label in classes:
        tmp = sum(dataset["class"] == label)
        class_prob += ((tmp) / len(dataset)) ** 2 
        # print(class_prob)
    # print(1 - class_prob) 
    return 1 - class_prob

# Split the elements into two datasets given a threshold, return split purity
def split_purity_given_thresh(dataset, attribute, threshold):
    # TODO: Find if there is a way to do the split using less columns
    # Split the datasets according to the threshold
    lower_than = dataset[dataset[attribute] <= threshold]
    greater_than = dataset[dataset[attribute] > threshold]

    return (Gini(lower_than) + Gini(greater_than))
    

# Build the tree according to best features given a dataset
def build_tree(data):
    node = Node()
    # print(f"SIZE OF THE DATASET: {len(data)}")
    # Handling the base cases
    if Gini(data) == 0 or data.shape[0] == 0:
        print("REACHED THE END OF THE RECURSION")

    best_gini = 1.0
    best_right, best_left = None, None
    best_feature = ""
    for attr in attributes:
        # Getting the column of every attribute in the dataset
        feature_col = data[attr].copy()

        # TODO: Make sure the values are being sorted correctly
        feature_col.sort_values(ascending=True) 
        for value in range(0, len(feature_col) - 2):

            # Threshold is the average of two adjacent sorted values
           try:
                thresh = (feature_col[value] + feature_col[value + 1]) / 2
           except:

               thresh = 0

           #thresh = feature_col[value] if feature_col[value] != 0 else 0.01
           split_gini = split_purity_given_thresh(data, attr, thresh)
           if split_gini < best_gini:
                best_feature = attr
                best_right = data[data[attr] <= thresh]
                best_left  = data[data[attr] > thresh]
                best_gini = split_gini
                print(f"\tNew best_gini: {best_gini}, left of size: {len(best_left)}\tbest right {len(best_right)}") 

    node.feature_name = attr
    node.threshold = thresh
    print(f"RECURSING with right data{best_right.shape}\tbest left: {best_left.shape}")
    node.left = build_tree(best_left)
    node.right = build_tree(best_right)
    
    print(f"best gini: {best_gini}")
    return node
build_tree(x_data)
