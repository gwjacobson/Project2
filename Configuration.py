
import numpy as np
import pylab
import matplotlib.pyplot as plt
import math
import plotly.graph_objects as go

#getting file of binary numbers
binary_file = open("configs", "r")

#array containing bits and their quantities
bit_array = []


for line in binary_file:
    my_string = line[-10:] #get the binary number
    my_string.strip()
    bit = int(my_string, 2) #change binary into bit
    
    bit_array.append(bit) #add bit to array containing all bits

bit_array.sort()
bit = [] #array for each different bit
count = [] #array for each bit's occurences

for i in range(0, len(bit_array)-2):
    if bit_array[i] != bit_array[i + 1]:
        bit.append(bit_array[i])
        count.append(bit_array.count(bit_array[i]))

#print(bit)
#print(count)
error = []
for i in count:
    error.append((math.sqrt(count[i])))

fig = go.Figure()

plt.bar(bit, count)
plt.show()
