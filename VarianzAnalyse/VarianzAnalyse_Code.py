import numpy as np
from math import sqrt
c=5
n=16 
#matrix 
#spalten: B,G,Y,R,IR
#zeilen: glasstyp 1-16
M = np.array([
    [ 0.60,  0.10,  0.69,  0.17,  0.45,  0.27,  1.74, -0.10, 2.02,  1.25,  1.37, -0.06,  5.03,  0.34,  5.16, -0.03 ],
    [ 0.92,  0.08,  0.44, -0.00,  0.60,  0.43,  1.67, -0.09, 1.93,  1.62,  1.28, -0.11,  4.90,  0.27,  4.77, -0.05 ],
    [ 1.12,  0.01,  0.18, -0.07,  0.57,  0.38,  4.38, -0.99, 3.94,  3.74,  3.67, -0.93,  4.43,  0.00,  4.51, -0.76 ],
    [ 1.46,  0.22,  0.50,  0.17,  1.23,  0.80,  2.35, -0.07, 2.50,  1.78,  1.58, -0.01,  5.12,  0.25,  5.06,  0.01 ],
    [ 5.40, -0.81,  5.32, -0.56,  5.42, -0.43,  5.42, -0.66, 5.49,  0.03,  5.42, -0.47,  5.42,  0.13,  5.40, -0.61 ]
])
# 
x = np.array([0.63,0.88,1.13,1.44,5.42])        #zuzuordnende Glasscheibe

def calc_Mittelwert():
    mu = np.zeros(c)
    for i in range(c):  #Zeile - je LED
        x_i = 0
        for k in range(n):  #Summe über alle n Glasstypen der Farbe i
            x_i += M[i,k]
        mu_i = x_i/n
        mu[i]=mu_i
    return mu

def calc_Streuung(Mittelwert):
    sigma = np.zeros(c)
    for i in range(c):
        sum_i = 0
        for k in range(n):
            sum_i += (M[i,k]-Mittelwert[i])**2
        sigma[i] = sum_i/n
    return sigma

def calc_Norm(mu,sigma):
    distance = np.zeros(n)
    for k in range(n):
        sum_k = 0
        for i in range(c):
            sum_k += ((x[i]-M[i,k])/sigma[i])**2
        distance[k] = sqrt(sum_k)
    return distance

def findClass(distance_array):
    distance_index_array = [[round(float(distance_array[k]),3),k] for k in range(n)]
    # print("index_array:",distance_index_array)
    distance_index_array.sort(key=lambda x: x[0])
    print("")
    # print("sorted_index_array:",distance_index_array)
    
    return distance_index_array

if __name__=="__main__":
    mu_array = calc_Mittelwert()
    sigma_array = calc_Streuung(mu_array)

    print("mu:",[float(v) for v in mu_array])
    
    print("sigma:",[float(v) for v in sigma_array])

    distance_array = calc_Norm(mu_array,sigma_array)
    # print(distance_array)
    distance_index_sorted = findClass(distance_array)
    sorted_indices = [distance_index_sorted[k][1] for k in range(n)]
    print(sorted_indices)        #gibt zugehörige Glassgruppe aus

    