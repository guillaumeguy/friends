import numpy as np
N = 2000
b = np.random.random_integers(0,1,size=(N,N))
b_symm = b.T * b
for i in range(N):
    b_symm[i][i] = 0

f=open('d.txt','a')
f.write(f"{N}\n")
np.savetxt(f, b_symm, delimiter="",fmt='%d')

