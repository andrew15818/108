import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 

#REMEMBER TO FOLLOW PEP8 GUIDELINES
#import the data from the csv, x and y values
train_df = pd.read_csv("train_data.csv")

#rows and columns of the training data.
xtrain = train_df['x_train']
ytrain = train_df['y_train']
print(xtrain)
print("We're making it to the end :D")
