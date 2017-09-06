'''
Created on Sep 6, 2017

@author: ejogarv
'''
from sys import stdin

class MineField(object):
    '''
    MineField class
    '''

    def __init__(self, rows, columns):
        '''
        Constructor
        '''
        self.board=[ [0] * columns for _ in range(rows)]
        
    def printBoard(self):
        ''' print
        '''
        for r in self.board:
            print("".join([str(c) for c in r]))
    
    def setMine(self, mineRow, mineCol):
        ''' Sets mine position
        '''
        self.board[mineRow][mineCol] = '*'
        
        #increase mine proximity counters in nearby positions
        for r in range(mineRow-1,mineRow+2):
            for c in range(mineCol-1,mineCol+2):
                try:
                    if (self.board[r][c] == '*'):
                        pass
                    elif r>=0 and c>=0:
                        self.board[r][c] = self.board[r][c] + 1
                except IndexError:
                    pass
    
class MineFieldReader():
    ''' Class resp. for building a MineField
    '''

    def reset(self):
        self.init = False
        self.rows = 0
        self.currentRow = 0

    def __init__(self):
        self.fieldCount=0
        self.valid=False
        self.reset()
        
    def readLine(self, line):
        if not self.init:
            # read rows and columns
            self.rows, columns = [int(c) for c in line.split(' ')]
            self.mf = MineField(self.rows, columns)
            self.init = True
            if self.rows == 0:
                self.valid = False
                return False
        else:
            for col in range(len(line)):
                if line[col] == '*':
                    self.mf.setMine(self.currentRow, col)
            self.currentRow += 1
            
        if self.currentRow < self.rows:
            return True
        else:
            self.fieldCount += 1
            self.reset()
            self.valid = True
            return False
        
    def mineField(self):
            return self.mf
    
        
def main():
    mfr = MineFieldReader()
    for line in stdin.read().splitlines():
        if len(line)==0:
            continue
        if mfr.readLine(line):
            pass
        elif mfr.valid:
            if mfr.fieldCount>1:
                print("")
            print("Field #{}:".format(mfr.fieldCount))
            mfr.mineField().printBoard()
        
if __name__ == "__main__":
    main()
