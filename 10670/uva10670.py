"""

"""

import sys
import re
import functools

def findCost(cost1, cost2, workload, target):
    cost = 0
    while (workload > target):
        half = workload >> 1
        if half >= target and (cost2 < cost1 * (workload - half)):
            cost += cost2
            workload = half
        else:
            cost += (workload-target) *cost1
            break

    return cost

def main():
    agency_pattern = r'(\w+):(\d+),(\d+)'
    regex = re.compile(agency_pattern)
    testcases = int(sys.stdin.readline())
    for i in range(0,testcases):
        print("Case {0}".format(i+1))
        (workload,target,nagencies) = map(int, sys.stdin.readline().split())
        agencies = []
        for _ in range(0,nagencies):
            (name, acost, bcost) = regex.match(sys.stdin.readline()).groups()
            agencies.append((name,int(acost), int(bcost)))

        agency_cost = [(findCost(a[1],a[2], workload,target),a[0]) for a in agencies]
        agency_cost.sort()
        print("\n".join(["{0} {1}".format(e[1],e[0]) for e in agency_cost]))

if __name__ == "__main__":
    main()