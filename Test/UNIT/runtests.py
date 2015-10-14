import os,sys
import getopt
import GAUREF.genref as GR
from tabulate import tabulate

class UnitTest:
    def __init__(self,infile,testClass,desc):
        self.infile    = infile
        self.testClass = testClass
        self.desc      = desc

class RespData:
    def __init__(self,energy,f):
        self.energy = energy
        self.f      = f

class MaxErrorExcedeed(Exception):
    def __init__(self,value):
        self.value = value
    def __str__(self):
        return repr(self.value)

#
#  Generate a Table of Unit Test input files
#  and their descriptions from "test.index"
#
#  This routine ignores lines with '#':
#  This can act as a convinient way to toggle
#  which tests actually run
#
def genTable():
    start = False
    f = open("test.index",'r')
    table = []
    for line in f:
        strx = line.split()
        if '-----' in line:
            start = True
            continue
        if start:    
            if ".inp" in line and '#' not in line:
                desc = ' '.join(strx[2:])
                entry = UnitTest(strx[0],strx[1],desc)
#                table.append([strx[0],desc])
                table.append(entry)
    f.close()
    return table

#
#  Checks whether file "name" exists in "path"
#
def findFile(name,path):
    found = False
    for root, dirs, files in os.walk(path):
        if name in files:
            found = True
            break
    return found

#
#  Generate a dictionary that maps test number string
#  of form "testXXXX" to array that holds reference
#  values.
#
#  No assumption is made of the class of test
#
def genRefDict():
    ref = open("GAUREF/ref.val",'r')
    refdict = {}
    for line in ref:
        strx=line.split('/')
        refdict[strx[0]] = strx[1:]
    
    for i in refdict:
        for j in range(len(refdict[i])):
            try: # SCF tests
                refdict[i][j] = float(refdict[i][j])
                reftype[i] = 'SCF'
            except ValueError: # RESP tests
                if ',' in refdict[i][j]: 
                     sp = refdict[i][j].split(',')
                    refdict[i][j] = RespData(float(sp[0]),float(sp[1]))
                    reftype[i] = 'RESP'
                else:
                    raise
            
    ref.close()
    return refdict

#
#  Prints the results in summary.txt
#
def genSummary(testtable,summary):
    outf = open('summary.txt','w')

# SCF output    
    headers = ["Test Job","|dEnergy|","max(|dDipole|)","max(|dQuadrupole|)","max(|dOctupole|)","Passed"]
    sumrytable = []
    j = 0
    for i in testtable:
        if 'SCF' in reftype[i.infile[:8]]:
            entry = []
            entry.append(testtable[j].infile.replace(".inp",''))
            entry.append(summary[j][0])
            entry.append(max(summary[j][1:4]))
            entry.append(max(summary[j][5:11]))
            entry.append(max(summary[j][12:22]))
            if summary[j][0] < 1E-7 and max(summary[j][1:4]) < 1E-7 and max(summary[j][5:11]) < 1E-7 and max(summary[j][12:22]) < 1E-7:
                entry.append('YES')
            else:
                entry.append('** NO **')
            sumrytable.append(entry)
        j += 1
    outf.write(tabulate(sumrytable,headers,tablefmt="simple",floatfmt=".4E"))

# RESP output
    headers = ["Test Job","max(|omega|)","max(|f|)","NStates","Passed"]
    sumrytable = []
    j = 0
    for i in testtable:
        if 'RESP' in reftype[i.infile[:8]]:
            entry = []
            entry.append(testtable[j].infile.replace(".inp",''))
            entry.append(summary[j][0])
            entry.append(summary[j][1])
            entry.append(nstates[j])
            if summary[j][0] < 1E-4 and summary[j][1] < 1E-4:
                entry.append('YES')
            else:
                entry.append('** NO **')
            sumrytable.append(entry)
        j += 1
    outf.write("\n\n")
    outf.write(tabulate(sumrytable,headers,tablefmt="simple",floatfmt=".4E"))

#
#  Runs Unit Tests
#
def runUnit(doKill,doPrint):
    global reftype, nstates
    reftype = {}
    testtable = genTable()
    refdict = genRefDict()
    summary = []
    nstates = {}

    k = 0
    for i in testtable:
        if findFile(i.infile,"."):
            if doPrint:
                print "../../chronusQ "+i.infile.replace(".inp",'')
            os.system("../../chronusQ "+i.infile.replace(".inp",'')+" > tmp")
            tmp = open("tmp",'r')
            line = tmp.readline()
            vals = line.split('/')
            line = tmp.readline()
            strx = line.split()
            time = float(strx[6])
            err = []
            engmax = 0.
            fmax   = 0.
#
#            store errors in summary
#
            for j in range(len(vals)):
                if 'SCF' in reftype[i.infile[:8]]:
                    try: 
                        abserr = abs(float(vals[j]) - refdict[i.infile[:8]][j])
                        err.append(abserr)
                        if abserr > 1E-7: raise MaxErrorExcedeed(abserr)
                    except MaxErrorExcedeed:
                        if doKill:
                            raise
                        else:
                            continue
                elif 'RESP' in reftype[i.infile[:8]]:
                    try:
                        nstates[k] = len(vals)
                        strx  = vals[j].split(',')
                        engtmp = abs(float(strx[0]) - refdict[i.infile[:8]][j].energy)
                        ftmp   = abs(float(strx[1]) - refdict[i.infile[:8]][j].f)
                        if (engtmp > engmax): engmax = engtmp 
                        if (ftmp > fmax): fmax = ftmp 
                        if engmax > 1E-4 or fmax > 1E-4: raise MaxErrorExcedeed(engmax)
                    except MaxErrorExcedeed:
                        if doKill:
                            raise
                        else:
                            continue
            if 'SCF' in reftype[i.infile[:8]]:
                summary.append(err)
            elif 'RESP' in reftype[i.infile[:8]]:
                err.append(engmax)
                err.append(fmax)
                summary.append(err)

        k += 1
    genSummary(testtable,summary)

#
#  Parse input options
#
if __name__ in "__main__":
    msg = """python runtests.py [-o --option]

  Options:
    -h, --help        Print usage instructions
    --enable-kill    Enable script termination on Unit Test failure
    --enable-travisci    Enable options for Travis-CI run
    -s, --silent        Disable Print"""
    doKill = False
    doPrint = True
    try:
        opts, args = getopt.getopt(sys.argv[1:],"hs",["enable-travisci","enable-kill","help","silent"])
    except getopt.GetoptError:
        print msg
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-h',"--help"):
            print msg
            sys.exit()
        elif opt in ("--enable-travisci","--enable-kill"):
            doKill = True
        elif opt in ('-s',"--silent"):
            doPrint = False

    runUnit(doKill,doPrint)    
