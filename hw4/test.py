
class Bellman_ford():
    def __init__(self,node_num:int,startedvertex:str):
        self.edges = []
        self.maxint = float('Inf')  #源点和某点不可达时的距离，无穷大
        self.dicts ={} #各边距离字典
        self.node_num = node_num #节点数
        self.startedvertex = startedvertex #源点字符
        self.strList = []
        self.dictsList = []

    #判断字典是否存在node的下标，否则添加字典,初始化值为maxint
    def has_node(self,nodes):
        for node in nodes:
            if node not in self.dicts.keys():
                self.dicts[node] = self.maxint
                self.strList.append(node)

    # 添加数据
    def add(self,start:str,end:str,weight:int):
        # start:有向边起点；end：有向边的终点；weight:有向边的权重
        self.has_node([start,end])
        self.edges.append({
            'start':start,
            'end':end,
            'weight':weight
        })
    #开始初始化
    def init(self):
        for dict in self.dicts.keys():
            self.dicts[dict] = self.maxint
        self.dicts[self.startedvertex] = 0
        #字符排序
        for i in range(len(self.strList)):
            for j in range(i):
                if self.strList[i] < self.strList[j]:
                    temp = self.strList[i]
                    self.strList[i] = self.strList[j]
                    self.strList[j] = temp
    def start(self):
        flag = 'true'
        # 初始化其他有向边的权重
        for i in range(self.node_num-1):
            for edge in self.edges:
                # 松弛逼近，不断地选择一条边，做松弛改进操作，直到得出正确的解答
                if self.dicts[edge['end']] > self.dicts[edge['start']] + edge['weight']:
                    self.dicts[edge['end']] = self.dicts[edge['start']] + edge['weight']
            temp = self.dicts.copy()
            self.dictsList.append(temp)

        for edge in self.edges:
            #判断是否存在负权回路的情况
            if self.dicts[edge['end']] > self.dicts[edge['start']] + edge['weight']:
                flag = 'false'
                break

        return {
            'dictsList':self.dictsList,
            'flag':flag
        }

if __name__ == "__main__":
    inp = input()
    inplist = inp.split(';')
    bf = None
    flag = 0
    for i in range(len(inplist)):
        if i == 1:
            bf = Bellman_ford(node_num=int(inplist[0]), startedvertex=inplist[1])
        elif i > 1:
            inpstr = inplist[i].split(',')
            bf.add(start=inpstr[0],end=inpstr[1],weight=int(inpstr[2]))
        if i == len(inplist)-1 and int(inplist[0]) != len(bf.strList):
            flag = 1
    if flag == 0:
        bf.init()
        rt = bf.start()
        print(";".join(["%s" %bf.strList[i] for i in range(len(bf.strList))]))
        for i in range(len(rt['dictsList'])):
            print(";".join(["%s" % rt['dictsList'][i][bf.strList[j]] for j in range(len(bf.strList))]))
        print(rt['flag'])
