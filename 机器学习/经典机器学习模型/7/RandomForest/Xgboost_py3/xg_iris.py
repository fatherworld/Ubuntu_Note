from __future__ import print_function
from __future__ import absolute_import
from __future__ import division
from sklearn import datasets
import sklearn
##使用鸢尾花数据集作为例子，这里用一个二分类做例子，因此只取数据集中label为0和1的，忽略最后的label=2的那一类。
iris = datasets.load_iris()
data = iris.data[:100]
print(data.shape)
label = iris.target[:100]
print(label)
##利用sklearn切分数据集
from sklearn.cross_validation import train_test_split
train_x, test_x, train_y, test_y = train_test_split(data, label, random_state=0)

#构建xgboost模型
import xgboost as xgb
dtrain=xgb.DMatrix(train_x,label=train_y)
dtest=xgb.DMatrix(test_x)

params={'booster':'gbtree',
    'objective': 'binary:logistic',
    'eval_metric': 'auc',
    'max_depth':4,
    'lambda':10,
    'subsample':0.75,
    'colsample_bytree':0.75,
    'min_child_weight':2,
    'eta': 0.025,
    'seed':0,
    'nthread':8,
     'silent':1}

watchlist = [(dtrain,'train')]
bst=xgb.train(params,dtrain,num_boost_round=100,evals=watchlist)##100棵树

ypred=bst.predict(dtest)

# 设置阈值, 输出一些评价指标
y_pred = (ypred >= 0.5)*1

from sklearn import metrics
print('AUC: %.4f' % metrics.roc_auc_score(test_y,ypred))
print('ACC: %.4f' % metrics.accuracy_score(test_y,y_pred))
print('Recall: %.4f' % metrics.recall_score(test_y,y_pred))
print('F1-score: %.4f' %metrics.f1_score(test_y,y_pred))
print('Precesion: %.4f' %metrics.precision_score(test_y,y_pred))
metrics.confusion_matrix(test_y,y_pred)

ypred = bst.predict(dtest)
print("测试集每个样本的得分\n",ypred)
ypred_leaf = bst.predict(dtest, pred_leaf=True)
print("测试集每棵树所属的节点数\n",ypred_leaf)

ypred_contribs = bst.predict(dtest, pred_contribs=True)
print("特征的重要性\n",ypred_contribs )

##利用sklearn里的randomforest

from sklearn.ensemble import RandomForestClassifier
model=RandomForestClassifier()
model.fit(train_x, train_y)
pred = model.predict(test_x)
acc = sklearn.metrics.accuracy_score(test_y, pred)
print('random forest acc:', acc)