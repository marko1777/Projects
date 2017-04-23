#! /usr/bin/env python
import re
import fileinput
import glob

sequence = ".*"
manual = "(\[\[).*(\]\])"
loop = "(CIKLUS)" + sequence + manual
branching = "(ELAGAZAS)" + sequence + manual

for file in glob.glob("*.prog"):
    inF = open(file,"r")
    outF = open(file.split(".")[0] + ".py","w")
    for itInF in inF:
        inFTemp = itInF.strip()
        matchValue = loop + "|" + branching + "|" + sequence 
        inFMap = re.match(matchValue,inFTemp)
        tempString = str(inFMap.group())
        if str(inFMap.group(1)) == "CIKLUS":
            tempString = tempString.replace("CIKLUS","for")
        if str(inFMap.group(4)) == "ELAGAZAS":
            tempString = tempString.replace("ELAGAZAS","if")
        tempString = tempString.replace("[[",":\n    ")
        while tempString.find(";") != -1: 
            tempString = tempString.replace(";","\n    ")
        prevTempString = tempString
        tempString = tempString.replace("]]","\n")
        if prevTempString == tempString:
            outF.write(tempString + "\n")            
        else:
            outF.write(tempString)
    inF.close()
    outF.close()