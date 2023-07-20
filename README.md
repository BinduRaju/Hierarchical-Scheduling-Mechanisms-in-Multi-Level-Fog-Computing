# Hierarchical-Scheduling-Mechanisms-in-Multi-Level-Fog-Computing
Fog Computing Project
This code is the implemetation of Scheduling mechanism for Hierarchical Fog Computing based on IEE paper -https://ieeexplore.ieee.org/document/9428571
The paper proposes a scheduling mechanism to effectively offload tasks in cloudlets based on their data transmissions. between the components
The algorithm is as follows-
The components in the cloudlet that is overloaded are considered
pick up the components that are not sources of the components in the same cloudlet and add them as sets to set of sets.
Now for each set of pick a component and add sets of all possible components that are sources to it in the same cloudlet
keep doing this until no new set is added
Now for each set formed find the impact
The impact is calculated as such for every edge within the same cloudlet and below we consider the impact is positive and for edges linking above the cloudlets we consider the impact as negative
After finding all the impacts we pick up the set with least impact and move it upwards.
