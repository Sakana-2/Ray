import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Line3D, Poly3DCollection
import numpy as np

class MyPlot:
    def __init__(self):
        fig = plt.figure(figsize = (8, 8))
        self.ax = fig.add_subplot(projection='3d')

        self.xrange = []
        self.yrange = []
        self.zrange = []
    def add_triangle(self,triangles):
        self.xrange = [np.min(triangles[0][:,0])-1,np.max(triangles[0][:,0])+1]
        self.yrange = [np.min(triangles[0][:,1])-1,np.max(triangles[0][:,1])+1]
        self.zrange = [np.min(triangles[0][:,2])-1,np.max(triangles[0][:,2])+1]

        self.ax.set_xlim(self.xrange)
        self.ax.set_ylim(self.yrange)
        self.ax.set_zlim(self.zrange)

        self.ax.add_collection(Poly3DCollection(triangles,color="r"))
    def add_line(self,start,direction):
        points = [[],[],[]]

        if direction[0] != 0: 
            for x in self.xrange:
                t = (x - start[0]) / direction[0]
                points[0].append(x)
                points[1].append(start[1]+t * direction[1])
                points[2].append(start[2]+t * direction[2])
        if direction[1] != 0:
            for y in self.yrange:
                t = (y - start[1]) / direction[1]
                points[0].append(start[0]+t * direction[0])
                points[1].append(y)
                points[2].append(start[2]+t * direction[2])
        if direction[2] != 0:
            for z in self.zrange:
                t = (z - start[2]) / direction[2]
                points[0].append(start[0]+t * direction[0])
                points[1].append(start[1]+t * direction[1])
                points[2].append(z)
        
        self.ax.plot(*points)
        # line = Line3D(*points,color="g")
        # self.ax.add_line(line,zorder=20)
    
    def show(self):
        plt.show()

triangles = np.array([
    ((3, 2, 1),(1, 2, 0.5),(2, 4, 4))
])
start = [0.5, 1, 2]
direction = [1, 1.4, 0.2]

m = MyPlot()
m.add_triangle(triangles)
m.add_line(start,direction)
m.show()