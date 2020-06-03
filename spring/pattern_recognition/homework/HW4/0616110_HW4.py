import numpy as np
import pandas as pd
import matplotlib as plt
from sklearn.svm import SVC, SVR
from sklearn.metrics import accuracy_score
from sklearn.model_selection import KFold # using this to split data

# ## Load data
x_train = np.load("x_train.npy")
y_train = np.load("y_train.npy")
x_test = np.load("x_test.npy")
y_test = np.load("y_test.npy")

# 550 data with 300 features
print(x_train.shape)

# It's a binary classification problem 
print(np.unique(y_train))

# use the mean square error to evaluate the performance of a given model
def mean_square_error():
    pass

# ## Question 1
# K-fold data partition: Implement the K-fold cross-validation function. 
# Your function should take K as an argument and return 
# a list of lists (len(list) should equal to K), which contains K elements. 
# Each element is a list contains two parts, the first part contains the index of all training folds, j
# e.g. Fold 2 to Fold 5 in split 1. The second part contains the index of validation fold, e.g. Fold 1 in  split 1

# 1. First we split the dataset into K parts
# 2. Take one of the K parts as validation, the rest as testing data
#   2.1 The validation one is used as "testing" to test the tmp model parameters
# 3. Choose the one that yields the best performance
def cross_validation(x_train, y_train, k=5):

    kf = KFold(n_splits=k, shuffle=True)
    
    # split the dataset into k folds, and select each one to be a validation set
    # Then choose the best one
    kfold_data = [] 
    for i, (train_index, val_index) in enumerate(kf.split(x_train)):
        #print("Split: %s, Training index: %s, Validation index: %s" % (i+1, train_index, val_index))
        kfold_data.append([train_index, val_index])
        
        # splitting the validation set
        # validation_sample = x_train[kfold_data[i][1]] 
        # testing_sample = x_train[kfold_data[i][1]]
    return kfold_data
    return NotImplementedError


kfold_data = cross_validation(x_train, y_train, k=10)

assert len(kfold_data) == 10 # should contain 10 fold of data
assert len(kfold_data[0]) == 2 # each element should contain train fold and validation fold
assert kfold_data[0][1].shape[0] == 55 # The number of data in each validation fold should equal to training data divieded by K


# ## example
'''
X = np.arange(20)
kf = KFold(n_splits=5, shuffle=True)
kfold_data= []
for i, (train_index, val_index) in enumerate(kf.split(X)):
    print("Split: %s, Training index: %s, Validation index: %s" % (i+1, train_index, val_index))
    kfold_data.append([train_index, val_index])

assert len(kfold_data) == 5 # should contain 5 fold of data
assert len(kfold_data[0]) == 2 # each element should contains index of training fold and validation fold
assert kfold_data[0][1].shape[0] == 4 # The number of data in each validation fold should equal to training data divieded by K
'''

# ## Question 2
# Using sklearn.svm.SVC to train a classifier on the provided train set and conduct the grid search of “C”, “kernel” and “gamma” to find the best parameters by cross-validation.

clf = SVC(C=1.0, kernel='rbf', gamma=0.01)
# Have to search for best combination of parameters
C = [0.1, 1, 10] 
Gamma = [0.01, 0.1, 1, 10]
# testing all the parameters of C and gamma and getting the ones that give a best fit
best_C = 0
best_gamma = 0
for c_test in C:
    for gamma_test in Gamma:
            clf = SVC(C=c_test, gamma=gamma_test)
            clf.fit(x_train, y_train)
            #print(clf)
            # get the performance using c and gamma of every fold, choose one with lowest MSE
            for row in range(len(kfold_data)):

                # the class labels of the elements in validation set
                class_indices = y_train[kfold_data[row][1]]

                # getting the predictions for the validation set based on decision function
                validation_results = clf.decision_function(
                        x_train[kfold_data[row][0]] 
                )
                validation_predictions = []
                print(accuracy score(class_indicex))

print(best_parameters)


# ## Question 3
# Plot the grid search results of your SVM. The x, y represents the hyperparameters of “gamma” and “C”, respectively. And the color represents the average score of validation folds
# You reults should be look like the reference image ![image](https://miro.medium.com/max/1296/1*wGWTup9r4cVytB5MOnsjdQ.png) 

# ## Question 4
# Train your SVM model by the best parameters you found from question 2 on the whole training set and evaluate the performance on the test set. **You accuracy should over 0.85**

y_pred = best_model.predict(x_test)
print("Accuracy score: ", accuracy_score(y_pred, y_test))


# ## Question 5
# Compare the performance of each model you have implemented from HW1

# ### HW1
train_df = pd.read_csv("../HW1/train_data.csv")
x_train = train_df['x_train'].to_numpy().reshape(-1,1)
y_train = train_df['y_train'].to_numpy().reshape(-1,1)

test_df = pd.read_csv("../HW1/test_data.csv")
x_test = test_df['x_test'].to_numpy().reshape(-1,1)
y_test = test_df['y_test'].to_numpy().reshape(-1,1)

print("Square error of Linear regression: ")
print("Square error of SVM regresssion model: ")

