import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

data_folder = "./"

trac_char = pd.read_csv(data_folder + "traction_char.csv", sep="\s+", header=None)


ip1 = 1.2
ip2 = 2.78
ip = ip1*ip2

Dk = 0.86
rk = Dk / 2.0

rows, columns = trac_char.shape

M_gp = np.zeros(rows)
omega_gp = np.zeros(rows)


for i in range(0, rows):
    
    M_gp[i] = trac_char[1][i] * 1000 * rk / ip / 2.0
    
    omega_gp[i] = trac_char[0][i] / 3.6 / rk * ip
    
    pass

k_gt_max = 3.0
Mmax = M_gp[0] / k_gt_max

n_max = 2500.0
omega_max = math.pi * n_max / 30.0

i_k = np.zeros(rows)
k_gt = np.zeros(rows)

for i in range(0, rows):
    
    i_k[i] = omega_gp[i] / omega_max    
    k_gt[i] = M_gp[i] / Mmax
    
    
plt.figure(figsize=(16,8))
plt.rcParams.update({'font.size': 22})
    
#plt.ylim(0.0, 4.0)
#plt.plot(i_k, k_gt, color=(0.5, 0.0, 0.0), linewidth=0.75) 

#plt.ylim(0.0, 100.0)
#plt.plot(trac_char[0], trac_char[1], color=(0.5, 0.0, 0.0), linewidth=0.75) 
    
gdt_file = open("gdt.csv", "w")

for i in range(0, rows):
    gdt_file.write(str(i_k[i]) + " " + str(k_gt[i]) + "\n")

gdt_file.close()  


gdm = pd.read_csv("../cfg/vehicles/ra3-head/gdm.csv", sep="\s+", header=None)

plt.ylim(0.0, 2.0)
plt.plot(gdm[0], gdm[1], color=(0.5, 0.0, 0.0), linewidth=0.75)  