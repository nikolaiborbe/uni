import matplotlib.pyplot as plt
fig=plt.figure()
################################### Experimental data
#Volum=[15.7, ... 47.1] # ml
#Volum=[v-Volum[0] for v in Volum]
#Potential=[-131, ... 204] # mV
Volum=[15.7, 39, 47.1] # ml
Volum=[v-Volum[0] for v in Volum]
Potential=[-131, 0, 204] # mV
################################### Plot
plt.plot(Volum,Potential,marker='+',linestyle='-')
plt.grid()
################################### save plot
plt.ylabel('$E$ [mV]')
plt.xlabel('$V$ [ml]')
#plt.savefig('plot.pdf')
plt.show()