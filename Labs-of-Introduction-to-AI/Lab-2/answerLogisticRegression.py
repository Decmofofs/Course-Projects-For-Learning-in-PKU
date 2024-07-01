import numpy as np

# 超参数
# TODO: You can change the hyperparameters here
lr = 0.25717 # 学习率
wd = 0.0000000000001 # l2正则化项系数


def predict(X, weight, bias):
    """
    使用输入的weight和bias，预测样本X是否为数字0。
    @param X: (n, d) 每行是一个输入样本。n: 样本数量, d: 样本的维度
    @param weight: (d,)
    @param bias: (1,)
    @return: (n,) 线性模型的输出，即wx+b
    """
    # TODO: YOUR CODE HERE
    reweight = weight.reshape(weight.shape[0],1)
    ans = X@reweight
    ans += bias[0]
    return ans.reshape(X.shape[0])
    raise NotImplementedError

def sigmoid(x):
    return 1 / (np.exp(-x) + 1)


def step(X, weight, bias, Y):
    """
    单步训练, 进行一次forward、backward和参数更新
    @param X: (n, d) 每行是一个训练样本。 n: 样本数量， d: 样本的维度
    @param weight: (d,)
    @param bias: (1,)
    @param Y: (n,) 样本的label, 1表示为数字0, -1表示不为数字0
    @return:
        haty: (n,) 模型的输出, 为正表示数字为0, 为负表示数字不为0
        loss: (1,) 由交叉熵损失函数计算得到
        weight: (d,) 更新后的weight参数
        bias: (1,) 更新后的bias参数
    """
    # TODO: YOUR CODE HERE
    SampleCount = X.shape[0]
    SampleDim = X.shape[1]
    out_1 = predict(X,weight,bias)
    out_1 *= Y
    def sig(x):
        if(x>100):
            return 0.999999999999
        elif(x<-100):
            return 0.000000000001
        else:
            return sigmoid(x)
    out_1 = np.vectorize(sig)(out_1)
    out_2 = np.log(out_1+1e-5)

    loss = np.sum(out_2)/SampleCount+wd*np.sum(weight*weight)
    partial_weight = np.zeros(SampleDim);partial_bias = 0
    for i in range(SampleCount):
        partial_weight += (1-out_1[i])*Y[i]*X[i]
        partial_bias += (1-out_1[i])*Y[i]
    partial_weight = (-1)*partial_weight/SampleCount
    partial_bias = (-1)*partial_bias/SampleCount
    for i in range(SampleDim):
        partial_weight[i] += 2*wd*weight[i]
    
    new_weight = weight-lr*partial_weight
    new_bias = np.array([bias[0]-lr*partial_bias])
    return(predict(X,weight,bias),loss,new_weight,new_bias)
    raise NotImplementedError
