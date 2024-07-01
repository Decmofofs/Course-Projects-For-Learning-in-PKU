import numpy as np
from typing import List
from utils import TreeNode
from simuScene import PlanningMap


### 定义一些你需要的变量和函数 ###
STEP_DISTANCE = 2
TARGET_THREHOLD = 0.25
TRY_TIMES = 20
### 定义一些你需要的变量和函数 ###

def get_dis(p_1,p_2):
    return np.sum(np.sqrt((p_1-p_2)*(p_1-p_2)))

def can_arrive(a,p1,p2):
    return  not a.map.checkline(p1.tolist(),p2.tolist())[0]

class RRT:
    def __init__(self, walls) -> None:
        """
        输入包括地图信息，你需要按顺序吃掉的一列事物位置 
        注意：只有按顺序吃掉上一个食物之后才能吃下一个食物，在吃掉上一个食物之前Pacman经过之后的食物也不会被吃掉
        """
        self.map = PlanningMap(walls)
        self.walls = walls
        
        # 其他需要的变量
        ### 你的代码 ###      
        self.nextfood = None
        self.remaining_try_times = None
        self.idx_in_path = None
        ### 你的代码 ###
        
        # 如有必要，此行可删除
        self.path = None
        
        
    def find_path(self, current_position, next_food):
        """
        在程序初始化时，以及每当 pacman 吃到一个食物时，主程序会调用此函数
        current_position: pacman 当前的仿真位置
        next_food: 下一个食物的位置
        
        本函数的默认实现是调用 build_tree，并记录生成的 path 信息。你可以在此函数增加其他需要的功能
        """
        
        ### 你的代码 ###      
        self.nextfood = next_food
        self.idx_in_path = 0
        self.remaining_try_times = TRY_TIMES
        ### 你的代码 ###
        # 如有必要，此行可删除
        self.path = self.build_tree(current_position, next_food)
        
        
    def get_target(self, current_position, current_velocity):
        """
        主程序将在每个仿真步内调用此函数，并用返回的位置计算 PD 控制力来驱动 pacman 移动
        current_position: pacman 当前的仿真位置
        current_velocity: pacman 当前的仿真速度
        一种可能的实现策略是，仅作为参考：
        （1）记录该函数的调用次数
        （2）假设当前 path 中每个节点需要作为目标 n 次
        （3）记录目前已经执行到当前 path 的第几个节点，以及它的执行次数，如果超过 n，则将目标改为下一节点
        
        你也可以考虑根据当前位置与 path 中节点位置的距离来决定如何选择 target
        
        同时需要注意，仿真中的 pacman 并不能准确到达 path 中的节点。你可能需要考虑在什么情况下重新规划 path
        """
        target_pose = np.zeros_like(current_position)
        ### 你的代码 ###
        while True:
            if(self.idx_in_path<len(self.path)-1):
                if(can_arrive(self,current_position,self.path[self.idx_in_path+1])):
                    self.remaining_try_times = TRY_TIMES
                    self.idx_in_path += 1
                    return self.path[self.idx_in_path]
            if(self.remaining_try_times==0):
                self.find_path(current_position,self.nextfood)
                continue
            target_pose = self.path[self.idx_in_path]
            self.remaining_try_times -= 1
            if not can_arrive(self,current_position,target_pose):
                self.find_path(current_position,self.nextfood)
                continue
            return target_pose
        ### 你的代码 ###
        return target_pose
        
    ### 以下是RRT中一些可能用到的函数框架，全部可以修改，当然你也可以自己实现 ###
    def build_tree(self, start, goal):
        """
        实现你的快速探索搜索树，输入为当前目标食物的编号，规划从 start 位置食物到 goal 位置的路径
        返回一个包含坐标的列表，为这条路径上的pd targets
        你可以调用find_nearest_point和connect_a_to_b两个函数
        另外self.map的checkoccupy和checkline也可能会需要，可以参考simuScene.py中的PlanningMap类查看它们的用法
        """
        path = []
        graph: List[TreeNode] = []
        graph.append(TreeNode(-1, start[0], start[1]))
        ### 你的代码 ###
        rev_graph: List[TreeNode] = []; rev_graph.append(TreeNode(-1,goal[0],goal[1]))
        meet_Node = None ;rev_meet_Node = None
        
        def check_if_meet_with_rev_graph(point):
            for i in range(len(rev_graph)):
                if can_arrive(self,point,rev_graph[i].pos):
                    return i
            return -1
        def check_if_meet_with_graph(point):
            for i in range(len(graph)):
                if(can_arrive(self,point,graph[i].pos)):
                    return i
            return -1

        while True:
            point=np.array([float(self.map.height*np.random.random(1)),float(self.map.width*np.random.random(1))]); rev_point=np.array([float(self.map.height*np.random.random(1)),float(self.map.width*np.random.random(1))])
            nearist_idx = self.find_nearest_point(point,graph)[0]; nearist_pos = graph[nearist_idx].pos
            rev_nearist_idx = self.find_nearest_point(rev_point,rev_graph)[0]; rev_nearist_pos = rev_graph[rev_nearist_idx].pos
            is_empty,newpoint = self.connect_a_to_b(nearist_pos,point); rev_is_empty,rev_newpoint = self.connect_a_to_b(rev_nearist_pos,rev_point)
            if is_empty:
                graph.append(TreeNode(nearist_idx,newpoint[0],newpoint[1]))
                x = check_if_meet_with_rev_graph(newpoint)
                if x > -1 :
                    meet_Node = graph[-1]
                    rev_meet_Node = rev_graph[x]
                    break
            if rev_is_empty:
                rev_graph.append(TreeNode(rev_nearist_idx,rev_newpoint[0],rev_newpoint[1]))
                x = check_if_meet_with_graph(rev_newpoint)
                if x > -1 :
                    meet_Node = graph[x]
                    rev_meet_Node = rev_graph[-1]
                    break
        node = meet_Node
        path_part_1 = []
        while True:
            path_part_1.append(node.pos)   
            if(node.parent_idx==-1):
                break
            node = graph[node.parent_idx]   
        node = rev_meet_Node
        path_part_2 = []
        while True:
            path_part_2.append(node.pos)
            if(node.parent_idx==-1):
                break
            node = rev_graph[node.parent_idx]
        path_part_1.reverse()
        path = path_part_1+path_part_2          
        ### 你的代码 ###
        return path

    @staticmethod
    def find_nearest_point(point, graph):
        """
        找到图中离目标位置最近的节点，返回该节点的编号和到目标位置距离、
        输入：
        point：维度为(2,)的np.array, 目标位置
        graph: List[TreeNode]节点列表
        输出：
        nearest_idx, nearest_distance 离目标位置距离最近节点的编号和距离
        """
        nearest_idx = -1
        nearest_distance = 10000000.
        ### 你的代码 ###
        for i in range(len(graph)):
            if(get_dis(point,graph[i].pos)<nearest_distance):
                nearest_distance = get_dis(point,graph[i].pos)
                nearest_idx = i
        ### 你的代码 ###
        return nearest_idx, nearest_distance
    
    def connect_a_to_b(self, point_a, point_b):
        """
        以A点为起点，沿着A到B的方向前进STEP_DISTANCE的距离，并用self.map.checkline函数检查这段路程是否可以通过
        输入：
        point_a, point_b: 维度为(2,)的np.array，A点和B点位置，注意是从A向B方向前进
        输出：
        is_empty: bool，True表示从A出发前进STEP_DISTANCE这段距离上没有障碍物
        newpoint: 从A点出发向B点方向前进STEP_DISTANCE距离后的新位置，如果is_empty为真，之后的代码需要把这个新位置添加到图中
        """
        is_empty = False
        newpoint = np.zeros(2)
        ### 你的代码 ###
        newpoint = STEP_DISTANCE/get_dis(point_a,point_b)*(point_b-point_a)+point_a
        is_empty = can_arrive(self,point_a,newpoint)
        ### 你的代码 ###
        return is_empty, newpoint

