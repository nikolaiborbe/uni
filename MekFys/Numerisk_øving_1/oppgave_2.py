import matplotlib.pyplot as plt

values_for_funk = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
funk_values = [9, -8, -29, -48, -59, -56, -33, 16, 97, 216] 

plt.figure(1)  # Initialize a new figure
plt.plot(values_for_funk, funk_values, '--r')  #  Plot x-vals and y-vals
plt.xlabel('x-verdier', fontsize=8)  # Add name to x-axis, change fontsize
plt.ylabel('y-verdier', fontsize=8)  # Add name to y-axis, change fontsize
plt.title('En kvadratisk funksjon')  # Add title to the figure
plt.xticks(fontsize=14)  # Change fontsize of x-ticks
plt.yticks(fontsize=14)  # Change fontsize of y-ticks
plt.show()  # Show the figure
