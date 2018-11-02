#Generating Nodes
import random 
nodesList=list()
s=5
for x in range(s):
  nodesList.append([random.randint(0, 30),random.randint(0, 30)])


#Generating Distance
import math
distMatrix=list(range(s))
row=list(range(s))
i=0;
for x in nodesList:
  j=0
  for y in nodesList:
    d=math.sqrt((y[1]-x[1])**2 + (y[0]-x[0])**2)
    row[j]=(2*d)
    j=j+1
  #print(row)
  distMatrix[i]=row[:]
  i=i+1
  #print(distMatrix)
  

#Printing the List
print("==========The Initial Edge Weights are:=========")
for x in distMatrix:
  print(x)
#distMatrix[3][2]=4
#distMatrix[2][3]=4

#Applying Floyd Warshal Algorithm
for im in range(s):
    #Individual Weights for Intermediate Nodes
    for i in range(s):
        for j in range(s):
            distMatrix[i][j]=min(distMatrix[i][j], distMatrix[i][im]+distMatrix[im][j])



##Printing the Final Output
print("===========The Final Least Costs are:===========")
for x in distMatrix:
  print(x)

    
