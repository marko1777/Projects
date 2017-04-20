#! /usr/bin/env python
import re
import fileinput
import glob

sequence = "+(\s;).+|.+"
anything = ".+?\s(\[\[).+?\s(\".+\"|\w+)((\s*;)|(\]\])).+?\s(\".+\"|\w+)((\s*;)|(\]\]))"
loop = "(C)IKLUS" + anything
branching = "(E)LAGAZAS" + anything

for file in glob.glob("*.prog"):
    inF = open(file,"r")
    for itInF in inF:
        inFTemp = itInF.strip()
        inFMap = re.match("loop|branching|sequence",inFTemp)
