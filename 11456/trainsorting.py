"""
Erin is an engineer.  She drives trains.  She also arranges the cars within each train.  She prefers to
put the cars in decreasing order of weight, with the heaviest car at the front of the train.
Unfortunately, sorting train cars is not easy. One cannot simply pick up a car and place it somewhere
else.  It is impractical to insert a car within an existing train.  A car may only be added to the beginning
and end of the train.
Cars arrive at the train station in a predetermined order.  When each car arrives, Erin can add it
to the beginning or end of her train, or refuse to add it at all.  The resulting train should be as long as
possible, but the cars within it must be ordered by weight.
Given the weights of the cars in the order in which they arrive, what is the longest train that Erin
can make?

Input
The first line is the number of test cases to follow.  The test cases follow, one after another; the format
of each test case is the following:
The first line contains an integer 0 <= n <= 2000, the number of cars.  Each of the following n lines
contains a non-negative integer giving the weight of a car.  No two cars have the same weight.

Output
Output a single integer giving the number of cars in the longest train that can be made with the given
restrictions.
Sample Input
"""

from sys import stdin,stdout
from bisect import bisect_left, bisect_right

class LIS:
    def __init__(self):
        self.q = []
        self.lis = []

    def add(self, w):
        if (len(self.q) == 0):
            self.q.append(w)
            self.lis.append(len(self.q))
        elif self.q[-1] < w:
            # Extend wagond queue
            self.q.append(w)
            self.lis.append(len(self.q))
        else:
            # find the wagon position
            pos = bisect_left(self.q, w)
            self.q[pos] = w
            self.lis.append(pos+1)

    def lis_i(self,i):
        return self.lis[i]

class LDS:
    def __init__(self):
        self.q = []
        self.lds = []

    def add(self, w):
        if len(self.q) == 0:
            self.q.append(w)
            self.lds.append(len(self.q))
        elif self.q[0] > w:
            # Extend wagon queue
            self.q.insert(0,w)
            self.lds.append(len(self.q))
        else:
            # find the wagon position
            pos = bisect_left(self.q, w)
            self.q[pos-1] = w
            self.lds.append(len(self.q) - (pos-1))

    def lds_i(self,i):
        return self.lds[i]


class ErinTrain:

    def __init__(self):
        self.lis = LIS()
        self.lds = LDS()
        self.ws= []

    def add(self, w):
        self.ws.append(w)

    def longestTrain(self):
        for w in reversed(self.ws):
            self.lds.add(w)
            self.lis.add(w)

        ret = 0
        # compute the max
        for i in range(0,len(self.ws)):
            # LIS from i to end
            lis_i = self.lis.lis_i(i)
            # LDS from i to end
            lds_i = self.lds.lds_i(i)

            if (lis_i + lds_i - 1) > ret:
                ret = lis_i + lds_i - 1

        return ret


if __name__ == "__main__":
    # read number of tests
    ntests = int(stdin.readline())

    for _ in range(ntests):
        et = ErinTrain()
        ncars = int(stdin.readline())
        for _ in range(ncars):
            n = int(stdin.readline())
            et.add(n)
        stdout.write("{0}\n".format(et.longestTrain()))
