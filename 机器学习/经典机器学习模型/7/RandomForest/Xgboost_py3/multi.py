# -*- coding: utf-8 -*-
"""
Created on Wed May 24 14:31:21 2017

@author: yeshan
"""

#coding=utf-8
from sklearn import metrics
from sklearn import cross_validation
from sklearn.svm import SVC
from sklearn.multiclass import OneVsRestClassifier
from sklearn.preprocessing import MultiLabelBinarizer
import numpy as np
from numpy import random
from sklearn import datasets
import numpy as np
from sklearn.metrics import accuracy_score

iris=datasets.load_iris()

X_train, X_test, y_train, y_test = cross_validation.train_test_split(iris.data, iris.target, test_size=0.6,random_state=0)
model = OneVsRestClassifier(SVC())
model.fit(X_train, y_train)
predicted = model.predict(X_test)
acc=accuracy_score(y_test, predicted)
print(acc)
from sklearn import svm

clf = svm.LinearSVC()

clf.fit(X_train, y_train)

predicted_2 = clf.predict(X_test)
acc_2=accuracy_score(y_test, predicted_2)
print(acc_2)
