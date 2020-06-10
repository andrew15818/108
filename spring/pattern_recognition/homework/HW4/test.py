import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sb
from sklearn.svm import SVC, SVR
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import accuracy_score, mean_squared_error
from sklearn.model_selection import KFold # using this to split data

# ## Load data
x_train = np.load("x_train.npy")
y_train = np.load("y_train.npy")
x_test = np.load("x_test.npy")
y_test = np.load("y_test.npy")

# Have to search for best combination of parameters
C = [0.1, 1, 10] 
Gamma = [0.01, 0.1, 1, 10]
grid_params = {
'C' : [0.1, 1, 10],
'Gamma' : [0.01, 0.1, 1, 10] 
}
clf = SVC(C=10, kernel='rbf', gamma=10)
grid = GridSearchCV(estimator=clf, param_grid=grid_params, scoring='accuracy')

print(clf.get_params().keys())
#clf = grid.fit(x_train, y_train)

#clf.predict(x_test)

'''
pred = grid.predict(x_test)
print(f"accuracy score: {accuracy_score(y_test, pred)}")
'''
