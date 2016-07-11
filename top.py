import sys
import operator

(N,n) = [int(x) for x in sys.argv[1:]]

inputcnts = {}

f1 = open('inputcnts/'+str(N), 'r')
for line in f1:
    out = line.split('\t')[0]
    cnt = line.split('\t')[1]
    inputcnts[out] = int(cnt[:-1]);
f1.close()
sorted_inputcnts = sorted(inputcnts.items(), key=operator.itemgetter(1), reverse=True)
print sorted_inputcnts[:n]
