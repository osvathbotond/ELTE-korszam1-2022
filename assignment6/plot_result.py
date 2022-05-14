import numpy as np
import os
import sys
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

if len(sys.argv) > 1:
    data_location = sys.argv[1]
else:
    data_location = "cmake-build-release/result.txt"
    print("You can pass the cpp program's output's location to the script as a first argument. "
          f"Since you did not pass any, it will use the default \"{data_location}\".")

if len(sys.argv) > 2:
    image_location = sys.argv[2]
else:
    image_location = "result.png"
    print("You can pass the output image's desired location to the script as a second argument. "
          f"Since you did not pass any, it will use the default \"{image_location}\".")

if not os.path.isfile(data_location):
    print(f"The file {data_location} cannot be found! Are you sure it's there?")
    sys.exit(1)

n, t = np.loadtxt(data_location).T
def cubic(x, a, b, c, d):
    return a + b*x + c*x**2 + d*x**3

popt, pcov = curve_fit(cubic, n, t)
err = np.sqrt(np.diag(pcov))
print("The result of fitting the t(n) = a + b*n + c*n**2 + d*n**3 function:")
print(f"a = {popt[0]} += {err[0]}")
print(f"b = {popt[1]} += {err[1]}")
print(f"c = {popt[2]} += {err[2]}")
print(f"d = {popt[3]} += {err[3]}")
plt.figure(figsize=(16, 9))
plt.xlabel('N', fontsize=20)
plt.ylabel('time [s]', fontsize=20)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)
plt.grid()
plt.plot(n, t, label='measured')
plt.plot(n, cubic(n, *popt), label="fitted")
plt.legend(fontsize=16)
plt.show()
plt.savefig(image_location)