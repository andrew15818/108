import numpy as np
import pandas as pd
from sklearn import tree
from sklearn.metrics import accuracy_score
from sklearn.datasets import load_breast_cancer

data = load_breast_cancer()
feature_names = data['feature_names']
print(feature_names)

x_train = (pd.read_csv("x_train.csv"))
x_test = (pd.read_csv("x_test.csv"))
y_train = (pd.read_csv("y_train.csv"))
y_test = (pd.read_csv("y_test.csv"))

clf = tree.DecisionTreeClassifier(criterion='gini', max_depth=3)
clf = clf.fit(x_train, y_train)

print(accuracy_score(y_train, ))
tree.export_graphviz(clf, out_file='tree_test.dot')