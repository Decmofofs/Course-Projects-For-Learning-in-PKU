from typing import List
import numpy as np
from utils import Particle

### 可以在这里写下一些你需要的变量和函数 ###
COLLISION_DISTANCE = 1
MAX_ERROR = 50000
K=0.12
S_1 = 0.088  
S_2 = 0.0088  
### 可以在这里写下一些你需要的变量和函数 ###


def generate_uniform_particles(walls, N):
    """
    输入：
    walls: 维度为(xxx, 2)的np.array, 地图的墙壁信息，具体设定请看README关于地图的部分
    N: int, 采样点数量
    输出：
    particles: List[Particle], 返回在空地上均匀采样出的N个采样点的列表，每个点的权重都是1/N
    """
    all_particles: List[Particle] = []
    for _ in range(N):
        all_particles.append(Particle(1.0, 1.0, 1.0, 0.0))
    ## 你的代码 ###
    all_particles: List[Particle] = []
    x_min,y_min = np.min(walls,axis=0)
    x_max,y_max = np.max(walls,axis=0)
    for i in range(N):
        all_particles.append(Particle(np.random.uniform(x_min,x_max),np.random.uniform(y_min,y_max),np.random.uniform(-np.pi,np.pi),1.0/N))
    ### 你的代码 ###
    return all_particles


def calculate_particle_weight(estimated, gt):
    """
    输入：
    estimated: np.array, 该采样点的距离传感器数据
    gt: np.array, Pacman实际位置的距离传感器数据
    输出：
    weight, float, 该采样点的权重
    """
    weight = 1.0
    ### 你的代码 ###
    distance = np.sum(np.sqrt((estimated-gt)*(estimated-gt)))
    weight = np.exp(-K*distance)
    ### 你的代码 ###
    return weight


def resample_particles(walls, particles: List[Particle]):
    """
    输入：
    walls: 维度为(xxx, 2)的np.array, 地图的墙壁信息，具体设定请看README关于地图的部分
    particles: List[Particle], 上一次采样得到的粒子，注意是按权重从大到小排列的
    输出：
    particles: List[Particle], 返回重采样后的N个采样点的列表
    """
    resampled_particles: List[Particle] = []
    for _ in range(len(particles)):
        resampled_particles.append(Particle(1.0, 1.0, 1.0, 0.0))
    ### 你的代码 ###
    resampled_particles: List[Particle] = []
    N = len(particles)
    for i in range(N):
        for _ in range(int(particles[i].weight*N)):
            resampled_particles.append(Particle(particles[i].position[0], particles[i].position[1], particles[i].theta, 1.0/N))
    if (N > len(resampled_particles)):
        fill_particles = generate_uniform_particles(walls, N-len(resampled_particles))
        for i in fill_particles:
            x,y,t,w=i.position[0],i.position[1],i.theta,i.weight
            resampled_particles.append(Particle(x,y,t,w))
    for i in resampled_particles:
        i.position[0] += np.random.normal(0, S_1)
        i.position[1] += np.random.normal(0, S_1)
        i.theta += np.random.normal(0, S_2)
    ### 你的代码 ###
    return resampled_particles

def apply_state_transition(p: Particle, traveled_distance, dtheta):
    """
    输入：
    p: 采样的粒子
    traveled_distance, dtheta: ground truth的Pacman这一步相对于上一步运动方向改变了dtheta，并移动了traveled_distance的距离
    particle: 按照相同方式进行移动后的粒子
    """
    ### 你的代码 ###
    p.theta += dtheta
    p.position[0] += traveled_distance*np.cos(p.theta)
    p.position[1] += traveled_distance*np.sin(p.theta)
    ### 你的代码 ###
    return p

def get_estimate_result(particles: List[Particle]):
    """
    输入：
    particles: List[Particle], 全部采样粒子
    输出：
    final_result: Particle, 最终的猜测结果
    """
    final_result = Particle()
    ### 你的代码 ###
    def get_weight(p):  
        return p.weight
    particles.sort(key=get_weight,reverse=True)
    final_result = particles[0]
    ### 你的代码 ###
    return final_result