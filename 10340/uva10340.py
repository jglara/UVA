"""
Input
The input contains several testcases. Each is specified by two strings s, t of alphanumeric ASCII
characters separated by whitespace. Input is terminated by EOF.

Output
For each test case output, if s is a subsequence of t.
"""
import sys
from functools import reduce


def subsequence(s, t):
    for c in s:
        i = t.find(c)
        if (i == -1):
            return False
        else:
            t = t[i+1:]

    return True

def main():
    for line in sys.stdin.read().splitlines():
        (s, t) = line.split()
        if (subsequence(s, t)):
            sys.stdout.write("Yes\n")
        else:
            sys.stdout.write("No\n")


if __name__ == "__main__":
    try:
        main()
    except EOFError:
        pass
