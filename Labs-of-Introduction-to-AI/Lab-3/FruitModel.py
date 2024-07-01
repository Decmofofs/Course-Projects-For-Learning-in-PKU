import math
from SST_2.dataset import traindataset, minitraindataset
from fruit import get_document, tokenize
import pickle
import numpy as np
from importlib.machinery import SourcelessFileLoader
from autograd.BaseGraph import Graph
from autograd.BaseNode import *

class NullModel:
    def __init__(self):
        pass

    def __call__(self, text):
        return 0


class NaiveBayesModel:
    def __init__(self):
        self.dataset = traindataset(shuffle=False) # 完整训练集，需较长加载时间
        #self.dataset = minitraindataset(shuffle=False) # 用来调试的小训练集，仅用于检查代码语法正确性

        # 以下内容可根据需要自行修改，不修改也可以完成本题
        self.token_num = [{}, {}] # token在正负样本中出现次数
        self.V = 0 #语料库token数量
        self.pos_neg_num = [0, 0] # 正负样本数量
        self.count()

    def count(self):
        # TODO: YOUR CODE HERE
        # 提示：统计token分布不需要返回值
        for sample in self.dataset:
            text, label = sample
            self.pos_neg_num[label] += 1
            for token in text:
                if token not in self.token_num[label]:
                    self.token_num[label][token] = 0
                self.token_num[label][token] += 1
        tmp = np.unique(list((self.token_num[0].keys()))+list((self.token_num[1].keys())))
        self.V = len(tmp)
        #raise NotImplementedError # 填写完成后删除这句

    def __call__(self, text):
        # TODO: YOUR CODE HERE
        pos_prob = self.pos_neg_num[0] / sum(self.pos_neg_num)
        neg_prob = self.pos_neg_num[1] / sum(self.pos_neg_num)
        for token in text:
            pos_prob *= (self.token_num[0].get(token, 0) + 1) / (sum(self.token_num[0].values()) + self.V)
            neg_prob *= (self.token_num[1].get(token, 0) + 1) / (sum(self.token_num[1].values()) + self.V)
        if pos_prob > neg_prob:
            return 0
        else :
            return 1
        # 返回1或0代表当前句子分类为正/负样本
        raise NotImplementedError


def buildGraph(dim, num_classes, L): #dim: 输入一维向量长度, num_classes:分类数
    # 以下类均需要在BaseNode.py中实现
    # 也可自行修改模型结构
    nodes = [Attention(dim), relu(), LayerNorm((L, dim)), ResLinear(dim), relu(), LayerNorm((L, dim)), Mean(1), Linear(dim, num_classes), LogSoftmax(), NLLLoss(num_classes)]
    
    graph = Graph(nodes)
    return graph


save_path = "model/attention.npy"

class Embedding():
    def __init__(self):
        self.emb = dict() 
        with open("words.txt", encoding='utf-8') as f: #word.txt存储了每个token对应的feature向量，self.emb是一个存储了token-feature键值对的Dict()，可直接调用使用
            for i in range(50000):
                row = next(f).split()
                word = row[0]
                vector = np.array([float(x) for x in row[1:]])
                self.emb[word] = vector
        
    def __call__(self, text, max_len=100):
        # TODO: YOUR CODE HERE
        # 利用self.emb将句子映射为一个二维向量（LxD），注意，同时需要修改训练代码中的网络维度部分
        # 默认长度L为50，特征维度D为100
        # 提示: 考虑句子如何对齐长度，且可能存在空句子情况（即所有单词均不在emd表内）  
        words = text
        vectors = [self.emb[word] if word in self.emb else np.zeros(100) for word in words]
        while len(vectors) < max_len:
            vectors.append(np.zeros(100))
        return np.array(vectors[:max_len])    
        raise NotImplementedError


class AttentionModel():
    def __init__(self):
        self.embedding = Embedding()
        with open(save_path, "rb") as f:
            self.network = pickle.load(f)
        self.network.eval()
        self.network.flush()

    def __call__(self, text, max_len=100):
        X = self.embedding(text, max_len)
        X = np.expand_dims(X, 0)
        pred = self.network.forward(X, removelossnode=1)[-1]
        haty = np.argmax(pred, axis=-1)
        return haty[0]


class QAModel():
    def __init__(self):
        self.document_list = get_document()
        
    def tf(self, word, document):
        # TODO: YOUR CODE HERE
        # 返回单词在文档中的频度
        # document变量结构请参考fruit.py中get_document()函数
        
        tf_count = document.count(word)
        
        return tf_count / (len(document)+1)
        
        raise NotImplementedError  

    def idf(self, word):
        # TODO: YOUR CODE HERE
        # 返回单词IDF值，提示：你需要利用self.document_list来遍历所有文档
        # 注意python整除与整数除法的区别
        documents_containing_word = sum(1 for document in self.document_list if word in document['document'])
        
        return np.log(len(self.document_list) / (documents_containing_word+1))
        
        raise NotImplementedError
    
    def tfidf(self, word, document):
        # TODO: YOUR CODE HERE
        # 返回TF-IDF值
        return self.tf(word, document) * self.idf(word)
        
        raise NotImplementedError

    def __call__(self, query):
        query = tokenize(query) # 将问题token化
        # TODO: YOUR CODE HERE
        # 利用上述函数来实现QA
        # 提示：你需要根据TF-IDF值来选择一个最合适的文档，再根据IDF值选择最合适的句子
        # 返回时请返回原本句子，而不是token化后的句子，数据结构请参考README中数据结构部分以及fruit.py中用于数据处理的get_document()函数
        #TF*IDF:如果一个词在整个文档中出现的频率不高，但是在某个句子中出现的频率很高，那么这个词对这个句子的重要性就很高
        #query中的某些关键词对于给定的某个句子的重要性高，说明这个句子很可能是query的答案
        document_score = [sum(self.tfidf(word, document['document']) for word in query) for document in self.document_list]
        best_document_index = np.argmax(document_score)
        sentence_list = self.document_list[best_document_index]['sentences']
        sentence_score = [sum(np.log(sentence[0].count(word)/len(sentence_list)+1) * np.log(len(sentence_list)/(sum(1 for sentence in sentence_list if word in sentence[0])+1)) for word in query) for sentence in sentence_list]
        best_sentence_index = np.argmax(sentence_score)
        return sentence_list[best_sentence_index][1]
        raise NotImplementedError


modeldict = {
    "Null": NullModel,
    "Naive": NaiveBayesModel,
    "Attn": AttentionModel,
    "QA": QAModel,
}


if __name__ == '__main__':
    
    embedding = Embedding()
    lr = 0.0025   # 学习率
    wd1 = 0.001  # L1正则化
    wd2 = 0.01  # L2正则化
    #0.011 0.008 0.012 88
    #0.021 0.004 0.016 93
    #0.007 0.0003 0.010 93
    #0.0025 0.001 0.01 99
    batchsize = 128
    max_epoch = 10
    
    max_L = 100
    num_classes = 4
    feature_D = 100
    
    graph = buildGraph(feature_D, num_classes, max_L) # 维度可以自行修改

    # 训练
    # 完整训练集训练有点慢
    best_train_acc = 0
    dataloader = traindataset(shuffle=True) # 完整训练集
    #dataloader = minitraindataset(shuffle=True) # 用来调试的小训练集
    for i in range(1, max_epoch+1):
        hatys = []
        ys = []
        losss = []
        graph.train()
        X = []
        Y = []
        cnt = 0
        for text, label in dataloader:
            x = embedding(text, max_L)
            label = np.zeros((1)).astype(np.int32) + label
            X.append(x)
            Y.append(label)
            cnt += 1
            if cnt == batchsize:
                X = np.stack(X, 0)
                Y = np.concatenate(Y, 0)
                graph[-1].y = Y
                graph.flush()
                pred, loss = graph.forward(X)[-2:]
                hatys.append(np.argmax(pred, axis=-1))
                ys.append(Y)
                graph.backward()
                graph.optimstep(lr, wd1, wd2)
                losss.append(loss)
                cnt = 0
                X = []
                Y = []

        loss = np.average(losss)
        acc = np.average(np.concatenate(hatys)==np.concatenate(ys))
        print(f"epoch {i} loss {loss:.3e} acc {acc:.4f}")
        if acc > best_train_acc:
            best_train_acc = acc
            with open(save_path, "wb") as f:
                pickle.dump(graph, f)