#!/bin/python
#run with python3 generateDataWith.py > inputFile.in
import random
import sys

NUM_POINTS = int(sys.argv[1])
MAX_X = int(sys.argv[2])
MAX_Y = int(sys.argv[3 if len(sys.argv) == 4 else 2])

for i in range(0, NUM_POINTS):
    print(str(random.randint(0,MAX_X)) + " " + str(random.randint(0,MAX_Y)))
