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
from bisect import bisect_left

class ErinTrain:

    def __init__(self):
        self.ql = []
        self.qr = []

    def _add(q, weight):
        if (len(q) == 0):
            q.append(weight)
        if (q[-1] < weight):
            # Increase train length (right)
            q.append(weight)
        elif (weight < q[0]):
            # increase train length (left)
            q.insert(0, weight)
        else:
            # find the wagon position
            pos = bisect_left(q,weight)
            q[pos] = weight

    def add(self,weight):
        ErinTrain._add(self.qr,weight)
        ErinTrain._add(self.ql,-weight)

    def longestTrain(self):
        return max(len(self.qr), len(self.ql))

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
