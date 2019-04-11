#!/bin/python
#run with python3 generateDataWith.py > inputFile.in
import random

NUM_POINTS = 20
MAX_X = 100
MAX_Y = 100
for i in range(0, NUM_POINTS):
    print(str(random.randint(0,MAX_X)) + " " + str(random.randint(0,MAX_Y)))
