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
        is_leaf = False
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
    
# Find the best threshold and purity for a given attribute
def get_best_split_on_feature(data, attr):
    datarow = data[attr]
    datarow = datarow.sort_values(ascending=True)

    prob_lower, prob_greater = 0,0
    best_prob = 1
    best_thresh = 1


    for index, row in data.iterrows():

        try:
            thresh = (datarow[index] + datarow[index+1]) / 2
        except:
            thresh = datarow[index]

        # Split the dataset according to the threshold
        for label in classes:
            # TODO: Continue getting the Gini values
            # Compute Gini for each class value lower than threshold
            lower_than_thresh = sum((datarow <= thresh) & (data['class'] == label))
            lower_than_count = sum(datarow <= thresh)
            prob_lower += ((lower_than_thresh) / (lower_than_count)) ** 2 if lower_than_count > 0 else 0
            
            # Compute Gini for each class value greater  than threshold
            greater_than_thresh = sum((datarow > thresh) & (data['class'] == label))
            greater_than_count = sum(datarow > thresh)
            prob_greater += ((greater_than_thresh) / (greater_than_count)) ** 2 if greater_than_count > 0 else 0
            
            if (prob_lower + prob_greater) <= best_prob:
                best_prob = prob_lower + prob_greater
                best_thresh = thresh



            

    return best_prob, best_thresh

# Build the tree according to best features given a dataset
def build_tree(data):
    node = Node()

    print(f"\tLength of the dataset: {len(data)}")
    # Handling recursive cases
    if data.shape[0] == 0:
        return None
    data_purity = Gini(data)

    if data_purity == 0:

        node.is_leaf = True
        node.feature_name = data['class'].iloc[0]
        print(f"\tfeature name: {node.feature_name}")
        return node
    
    best_purity, best_thresh = 1, 1
    lower_than = None
    greater_than = None
    # Loop for all classes and all values of each feature
    for attr in attributes:
        # Get the column that containing the values of the feature
        datarow = data[attr]
        attr_purity, attr_thresh = get_best_split_on_feature(data, attr)
        print(f"\t\t{type(attr_purity)}\t{type(attr_thresh)}") 

        # TODO: Check if the purity for this attribute is lower than for others
        if attr_purity < best_purity: 
            best_purity = attr_purity
            best_thresh = attr_thresh
            best_attr = attr
            lower_than = data[data[best_attr] <= best_thresh]
            greater_than = data[data[best_attr] > best_thresh]
    
    # Recurse on the children
    print(lower_than)
    print("RECURSING ON THE LEFT CHILD")
    node.left = build_tree(lower_than)
    print("RECURSING ON THE RIGHT CHILD")
    node.right = build_tree(greater_than)


    return node
build_tree(x_data)
