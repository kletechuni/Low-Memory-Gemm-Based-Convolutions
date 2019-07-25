#This is the code for modified MEC which was implimented using simple for loops and sgemm from scipy package
# input array=1960x1960x3
# output array= 1958x1958x3


import numpy as np
from scipy import linalg


w=1960
h=1960
c=3
tk_w=3
tk_h=3


sf=-3
k_w=1
k_h=9
std_w=1
std_h=1
lowConc = []
#img=np.random.rand(w,h,c)

im = np.random.rand(w,h,c)
w,h,c = im.shape
ker=np.random.rand(k_h,k_w)
l_mat_0=np.zeros((1,tk_w*tk_h),float)
l_mat_1=np.zeros((1,tk_w*tk_h),float)
l_mat_2=np.zeros((1,tk_w*tk_h),float)
san=int(((w-tk_w)//std_h)+1)
sem=int((w-tk_w)//std_w)+1
o_mat=np.zeros((san,sem,3))


count=0
for i in range(int(((w-tk_w)//std_h)+1)):
	st=-1
	for p in range(int((w-tk_w)//std_w)+1):
		st=st+std_w
		for q in range(tk_h):
			for k in range(tk_w):
				l_mat_0[0,tk_w*q+k]=im[q,k+st,0]
				l_mat_1[0,tk_w*q+k]=im[q,k+st,1]
				l_mat_2[0,tk_w*q+k]=im[q,k+st,2]
		count=count+1
		o_mat[i,p,0]=linalg.blas.sgemm(1,l_mat_0,ker)
		o_mat[i,p,1]=linalg.blas.sgemm(1,l_mat_1,ker)
		o_mat[i,p,2]=linalg.blas.sgemm(1,l_mat_2,ker)
print(o_mat.shape)
print(count)
