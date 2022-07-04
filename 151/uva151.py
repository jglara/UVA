'''
Created on Sep 11, 2017

@author: ejogarv
'''

from sys import stdin


class PowerOffManager:
    def __init__(self, regions, final):
        self.regions = regions
        self.final = final
        
    def powerOffNext(self, rlist, index, M):
        region = rlist[index] 
        if (len(rlist)==1):
            del rlist[0]
            return 0, region
        else:
            new_index = (index-1 + M) % (len(rlist)-1)
            del rlist[index]
            return new_index, region
        
    def test(self, m):
        rlist = list(range(1, self.regions+1))
        index = 0
        po_list = []
        while True:
            index, region = self.powerOffNext(rlist, index, m)
            po_list.append(region)
            if region == self.final:
                break
        
        #print("Testing {} poweroff list = {} {}".format(m, po_list, len(rlist)))
        return len(rlist) == 0
    
    def findMinimal(self):
        M=1
        while True:
            if self.test(M):
                return M
            else:
                M+=1
            
        return None
        

if __name__ == '__main__':
    for line in stdin.read().splitlines():
        N = int(line)
        if N==0:
            break
        else:
            pm = PowerOffManager(N,13)
            print(pm.findMinimal())
