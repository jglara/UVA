'''
Created on Sep 7, 2017

@author: ejogarv
'''

from sys import stdin,stdout


class SnakeLadders:
    def __init__(self, players):
        self.currentPlayer = 0
        self.players = [1] * players
        self.jumps = {}
        self.finished = False
        
    def addJump(self, start, end):
        self.jumps[start] = end
        
    def update(self, dieRoll):
        if (self.finished):
            return
        
        self.players[self.currentPlayer] += dieRoll
        pos = self.jumps.get(self.players[self.currentPlayer])
        if pos:
            self.players[self.currentPlayer] = pos
        
        if (self.players[self.currentPlayer] >= 100):
            self.players[self.currentPlayer] = 100
            self.finished = True
        
        self.currentPlayer = (self.currentPlayer + 1) % len(self.players)
        
    def printOutput(self):
        stdout.writelines( ["Position of player {} is {}.\n".format(i+1, pos) for i,pos in enumerate(self.players)] ) 
        
def main():
    testcases = int(stdin.readline())
    for _ in range(testcases):
        players,jumps,rolls = [int(x) for x in stdin.readline().split()]
        #print("p={} j={} r={}".format(players,jumps,rolls))
        sl = SnakeLadders(players)
        for _ in range(jumps):
            start,end = stdin.readline().split()
            sl.addJump(int(start), int(end))
            
        for _ in range(rolls):
            sl.update( int( stdin.readline().split()[0]))
        
        sl.printOutput()
    

if __name__ == '__main__':
    main()