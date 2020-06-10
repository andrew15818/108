import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sb
from sklearn.svm import SVC, SVR
from sklearn.metrics import accuracy_score, mean_squared_error
from sklearn.model_selection import KFold # using this to split data


# Constants for HW1 model
ITERATIONS = 1000
LEARNING_RATE = 1e-2
SLOPE_GRADIENT = 1
INT_GRADIENT = 2

# Have to search for best combination of parameters
C = [0.1, 1, 10] 
Gamma = [0.01, 0.1, 1, 10]

# Store the accuracy of using C[i] and Gamma[j] for plotting 
plot_values = [[0] * len(Gamma)] * len(C)

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
def performance_measure(data):
    sum = 0
    for value in data:
        sum += value
    return (sum / len(data))

# Model function from Homework 1
def model(xtrain, ytrain):
    #values we try to maximize
    slope = 0
    intercept = 0 

    #turning the two original objects into 
    #numpy arrays
    X = np.array(xtrain)
    Y_original = np.array(ytrain)
    num_points = X.shape[0] #number of testing points

    for i in range(0,ITERATIONS):
        Y_predict = slope * X + intercept
        slope_gradient = (-2/num_points) * np.sum(X * (Y_original - Y_predict)) 
        int_gradient = (-2/num_points) * np.sum(Y_original - Y_predict)
        
        slope = slope - slope_gradient * LEARNING_RATE
        intercept = intercept - int_gradient * LEARNING_RATE
 

    return Y_predict, slope, intercept 


# Find best C and gamma for either classification or regression
def find_best_parameters(x_data, y_data, type="classification"):
    if type == "classification":
        clf = SVC(C=1.0, kernel='rbf', gamma=0.01) 

    else: 
        clf = SVR(C=1.0, kernel='rbf', gamma=0.01)

    
    best_C = 0
    best_performance = 0
    best_gamma = 0
    for i, c_test in enumerate(C):
        for j, gamma_test in enumerate(Gamma):
                if type == "classification":
                    clf = SVC(C=c_test, kernel='rbf' ,gamma=gamma_test)
                else:
                    clf = SVR(C=c_test, kernel='rbf',  gamma=gamma_test)


                # keep track of the performance of each fold
                fold_performance = [] 
                # get the performance using c and gamma of every fold, choose one with lowest MSE
                for row in range(len(kfold_data)):

                    # class indices of testing and validation sets
                    class_indices_training = y_data[kfold_data[row][0]]
                    class_indices_validation = y_data[kfold_data[row][1]]
                   

                    # Getting the actual input data from validation and testing indices
                    data_indices_training= x_data[kfold_data[row][0]]
                    data_indices_validation = x_data[kfold_data[row][1]]

                    clf.fit(data_indices_training, class_indices_training) 

                    # getting class predictions for given set
                    validation_predictions = clf.predict(data_indices_validation)
                     
                    #print(f"ground truth:{class_indices}")
                    #print(f"predicitons:{validation_predictions}\n")
                    if type == "classification":
                        accuracy = accuracy_score(class_indices_validation, validation_predictions)  
                    else:                        
                        accuracy = mean_squared_error(class_indices_validation, validation_predictions) 

                    fold_performance.append(accuracy)

                    print(f"\taccuracy for C={c_test} and gamma={gamma_test}\t{accuracy}")

                performance = performance_measure(fold_performance)
                print(f"fold_performance: {performance}")
                plot_values[i][j] = performance

                if performance > best_performance:
                    best_performance, best_C, best_gamma = performance, c_test, gamma_test


    return (best_performance, best_C, best_gamma) 

# ## Question 1
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

kfold_data = cross_validation(x_train, y_train, k=10)

assert len(kfold_data) == 10 # should contain 10 fold of data
assert len(kfold_data[0]) == 2 # each element should contain train fold and validation fold
assert kfold_data[0][1].shape[0] == 55 # The number of data in each validation fold should equal to training data divieded by K


# ## example

X = np.arange(20)
kf = KFold(n_splits=5, shuffle=True)
kfold_data= []
for i, (train_index, val_index) in enumerate(kf.split(X)):
    print("Split: %s, Training index: %s, Validation index: %s" % (i+1, train_index, val_index))
    kfold_data.append([train_index, val_index])

assert len(kfold_data) == 5 # should contain 5 fold of data
assert len(kfold_data[0]) == 2 # each element should contains index of training fold and validation fold
assert kfold_data[0][1].shape[0] == 4 # The number of data in each validation fold should equal to training data divieded by K


# ## Question 2
# Using sklearn.svm.SVC to train a classifier on the provided train set and conduct the grid search of “C”, “kernel” and “gamma” to find the best parameters by cross-validation.


# testing all the parameters of C and gamma and getting the ones that give a best fit
best_parameters = find_best_parameters(x_train, y_train, type="classification")

print(best_parameters)

# How to plot the image?
# ## Question 3
# Plot the grid search results of your SVM. The x, y represents the hyperparameters of “gamma” and “C”, respectively. And the color represents the average score of validation folds
# You reults should be look like the reference image ![image](https://miro.medium.com/max/1296/1*wGWTup9r4cVytB5MOnsjdQ.png) 
print(f"plot values: {plot_values}")
table = sb.heatmap(data=plot_values)
plt.show()

# TODO: figure out how to map the table with the different hyper parameters
# ## Question 4
# Train your SVM model by the best parameters you found from question 2 on the whole training set and evaluate the performance on the test set. **You accuracy should over 0.85**
# mock_predict(C, Gamma)

best_model = SVC(C=best_parameters[1], gamma=best_parameters[2])
best_model.fit(x_train, y_train)
y_pred = best_model.predict(x_test)
print("Accuracy score: ", accuracy_score(y_pred, y_test))


# ## Question 5
# Compare the performance of each model you have implemented from HW1

# ### HW1
train_df = pd.read_csv("../HW1/train_data.csv")
x_train = train_df['x_train'].to_numpy().reshape(-1,1)
y_train = train_df['y_train'].to_numpy().reshape(-1,1)

# Training a new regression model
clf = SVR(C=C[0], kernel='rbf', gamma=Gamma[0])
kfold_data = cross_validation(x_train, y_train, k=10)
best_parameters = find_best_parameters(x_train, y_train, type="regression")
clf = SVR(C=best_parameters[1], kernel='rbf', gamma=best_parameters[2])

# Re=running the model from HW1
hw1_y_predict, hw1_slope, hw1_intercept = model(x_train, y_train)
hw1_error = np.square(np.subtract(y_train, hw1_y_predict)).mean()

test_df = pd.read_csv("../HW1/test_data.csv")
x_test = test_df['x_test'].to_numpy().reshape(-1,1)
y_test = test_df['y_test'].to_numpy().reshape(-1,1)

# Comparing the results from Homework 1 to the current one
clf.fit(x_train, y_train)
svr_test_predictions = clf.predict(x_test)
svr_error = mean_squared_error(y_test, svr_test_predictions)

print(f"Square error of Linear regression: {hw1_error}")
print(f"Square error of SVM regresssion model: {mean_squared_error(y_test, svr_test_predictions)}")

