# -*- coding: utf-8 -*-
"""
This program solvs a simple electric in the textbook page file by FDM

Created on Fri Nov 25 09:48:46 2016
@author: ferris
"""
# %% setup 
import numpy as np
import matplotlib.pyplot as plt
from scipy.sparse import spdiags,linalg,eye
import mpl_toolkits.mplot3d
nx = 21;     # 设置网格节点数
ny = 16;     
v1 = [];     # 设置数组
v1 = np.ones((ny,nx));
v2 = np.zeros((ny,nx));
t = np.zeros((ny,nx)); 
v1[0,:]= np.ones((1,nx))*100;
v1[1:]= np.ones((ny-1,nx))*0;
k= 0;         # k 为return的次数
w= 0.0001;    # w 为设置的最大允许误差
z= 0;         # 迭代误差初值

#%% fdm
while z != 1 :
    for i in np.arange(1,ny-1) :
        for j in np.arange(1,nx-1):
            v2[i][j]= (v1[i-1][j]+v1[i][j-1]+v1[i][j+1]+v1[i+1][j])/4
            # 差分方程（简单迭代）
            t [i][j] = np.abs(v1[i][j]-v2[i][j]);
            v1[i][j] = v2[i][j];
    t;
    x=t < w;
    y = np.all(x);
    z = np.all(y);
    k = k+1;
plt.subplot(1,2,1);
plt.imshow(v1);
v3 = np.flipud(v1);
plt.subplot(1,2,2);
plt.contour(v3,20);
x = np.arange(1,nx) ;
y = np.arange(1,ny) ;
[xx,yy] = np.meshgrid(x,y);
[gx,gy] = np.gradient(-v3);
plt.quiver(gx,gy);
plt.show

            