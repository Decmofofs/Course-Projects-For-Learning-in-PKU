from numpy.random import rand
import mnist
from answerTree import *
import numpy as np

# 超参数
# TODO: You can change the hyperparameters here
num_tree = 10    # 树的数量
ratio_data = 0.9   # 采样的数据比例
ratio_feat = 0.3 # 采样的特征比例
hyperparams = {
    "depth":500, 
    "purity_bound":1e-2,
    "gainfunc": gain
    } # 每颗树的超参数


def buildtrees(X, Y):
    """
    构建随机森林
    @param X: n*d, 每行是一个输入样本。 n: 样本数量， d: 样本的维度
    @param Y: n, 样本的label
    @return: List of DecisionTrees, 随机森林
    """
    # TODO: YOUR CODE HERE
    # 提示：整体流程包括样本扰动、属性扰动和预测输出
    number_of_samples = int(X.shape[0] * ratio_data)
    number_of_features = int(X.shape[1] * ratio_feat)
    trees = []
    for i in range(num_tree):
        
        sample_indices = np.random.choice(X.shape[0], size=number_of_samples, replace=False)
        X_sample = X[sample_indices]
        Y_sample = Y[sample_indices]
        unused = list(np.random.choice(X.shape[1], size=number_of_features, replace=False))
        tree = buildTree(X_sample, Y_sample, unused, hyperparams["depth"], hyperparams["purity_bound"], hyperparams["gainfunc"])
        trees.append(tree)
    
    return trees
    
    raise NotImplementedError    

def infertrees(trees, X):
    """
    随机森林预测
    @param trees: 随机森林
    @param X: n*d, 每行是一个输入样本。 n: 样本数量， d: 样本的维度
    @return: n, 预测的label
    """
    pred = [inferTree(tree, X)  for tree in trees]
    pred = list(filter(lambda x: not np.isnan(x), pred))
    upred, ucnt = np.unique(pred, return_counts=True)
    return upred[np.argmax(ucnt)]
