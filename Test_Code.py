import matplotlib.pyplot as plt
import numpy as np
import math

Compass_Heading = 202
CourseToDestination = 350
Heading = math.radians(Compass_Heading)
Course = math.radians(CourseToDestination)

angle = Compass_Heading - CourseToDestination - 90

if math.sin(math.radians(angle)) > 0:
    # Go South
    print('Go South')
    print('North_Motor ON')
    theta_3 = np.full((10,1),math.radians(180))
else:
    # Go North
    print('Go North')
    print('South_Motor ON')
    theta_3 = np.full((10,1),math.radians(0))
if math.cos(math.radians(angle)) > 0:
    # Go West
    print('Go West')
    print('East_Motor ON')
    theta_4 = np.full((10,1),math.radians(270))
else:
    # Go East
    print('Go East')
    print('West_Motor ON')
    theta_4 = np.full((10,1),math.radians(90))

Compass_length = np.linspace(0,1,10)
Motor_length_NS = np.linspace(0,(math.cos(math.radians(angle))),10)
Motor_length_WE = np.linspace(0,(math.sin(math.radians(angle))),10)
theta_1 = np.full((10,1),Heading)
theta_2 = np.full((10,1),Course)

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
ax.plot(theta_1, Compass_length, label = 'Heading')
ax.plot(theta_2, Compass_length, label = 'Course')
#ax.plot(theta_3, Motor_length_NS, label = 'NS Motor')
#ax.plot(theta_4, Motor_length_WE, label = 'WE Motor')
ax.set_theta_direction(-1)
ax.set_theta_zero_location('N')
ax.set_yticklabels([])
plt.legend()
plt.show()
