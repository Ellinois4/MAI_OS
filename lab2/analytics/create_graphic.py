import matplotlib.pyplot as plt
import csv

X = []
Y = []



with open('/home/b_eli/Desktop/MAI_OS/lab2/analytics/metrics.txt', 'r') as datafile:
    plotting = csv.reader(datafile, delimiter=' ')
    
    for ROWS in plotting:
        X.append(float(ROWS[2]))
        Y.append(float(ROWS[0]))


for i in range(1, len(Y)):
    Y[i] = Y[0] / Y[i]


plt.plot(X[1:], Y[1:])
plt.title('Acceleration of workers stat')
plt.xlabel('Count of workers')
plt.ylabel('Acceleration')
plt.grid()
plt.show()

for i in range(1, len(Y)):
    Y[i] /= i + 1   

plt.plot(X[1:], Y[1:])
plt.title('Efficiency of workers stat')
plt.xlabel('Count of workers')
plt.ylabel('Efficiency')
plt.grid()
plt.show()