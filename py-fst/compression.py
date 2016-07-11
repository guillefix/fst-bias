import zlib
import sys

N = int(sys.argv[1])

for i in range(N):
    f1 = open('inputcnts/'+str(i), 'r')
    f2 = open('comp/'+str(i), 'w+')
    for line in f1:
        out = line.split('\t')[0]
        cnt = line.split('\t')[1]
        f2.write(str(len(zlib.compress(out, 5)))+'\t'+cnt+"\n")
    print i
    f1.close()
    f2.close()
