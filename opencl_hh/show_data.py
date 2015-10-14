import numpy as np
import matplotlib.pyplot as plt
import sys

argvs = sys.argv
argc = len(argvs)
if(argc != 2):
    print 'Usage : ./%s (input_filename)' % (argvs[0])
    quit()

targetfile = argvs[1]
data = np.loadtxt(targetfile, skiprows=3, delimiter=",")

t = data[:,0]
i = data[:,1]
v = data[:,2]

plt.subplot(211)
#plt.rcParams['font.size'] = 15
plt.xlabel("t [msec]")
plt.ylabel("Injected Current [uA]")
plt.ylim([-10.0,20.0])
plt.plot(t, i)

plt.subplot(212)
plt.xlabel("t [msec]")
plt.ylabel("Membrane Potential [mV]")
plt.ylim([-90,50])
plt.plot(t, v)
plt.show()
