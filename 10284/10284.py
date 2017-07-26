'''
Created on Jul 24, 2017

@author: ejogarv
'''

class Board:
    def __init__(self):
        self.free = [[True for i in range(0,8)] for j in range(0,8)]
        self.attacked = [[False for i in range(0,8)] for j in range(0,8)]
        self.pieces = []
        self.i = 0
        self.free_or_nonattacked = 64

    def read(self, fenDesc):
        row=-1
        for line in fenDesc.split('/'):
            row += 1
            col=-1
            for d in line:
                if d.isdigit():
                    col += int(d)
                else:
                    col += 1
                    #print "{0} {1} <- {2}".format(row,col,d)
                    self.setOcuppied(row,col)
                    self.pieces.append((row,col,d))

    def __getitem__(self,i):
        return self.pieces[i]

    def isFree(self,row,col):
        return self.free[row][col]

    def setOcuppied(self,row,col):
        if (self.free[row][col]):
            self.free[row][col] = False
            self.free_or_nonattacked -=1

    def setAttacked(self,row,col):
        if (not self.attacked[row][col]):
            self.attacked[row][col] = True
            self.free_or_nonattacked -=1

    def getFreeNonattacked(self):
        return self.free_or_nonattacked

def validPosition(row, col, board):
    if (row < 0) or (row >7):
        return False
    elif ((col < 0) or (col >7)):
        return False
    
    return board.isFree(row,col)


def PositionGenerator(board, row,col,deltaRow,deltaCol, times=-1):
    while times != 0:
        row = row + deltaRow
        col = col + deltaCol
        if validPosition(row, col, board):
            times = times - 1
            yield row, col
        else:
            return

def MultiplePositionGenerator(board, row, col, aList):
    for l in aList:
        (deltaRow, deltaCol, times) = l
        pg = PositionGenerator(board,row,col,deltaRow,deltaCol,times)
        for p in pg:
            yield p 
    

mpGen = { 'P' : [(-1, -1, 1), (-1, 1, 1)],
          'p' : [(1, -1, 1), (1, 1, 1)],
             
            'N' : [(2, -1, 1), (2, 1, 1),
                       (1, 2, 1), (-1, 2, 1),
                       (-2, 1, 1), (-2, -1, 1),
                       (1, -2, 1), (-1, -2, 1)],
         
            'B' : [(1, 1, -1), (-1, 1, -1), (1, -1, -1), (-1, -1, -1)],
         
            'R' : [(1, 0, -1), (-1, 0, -1), (0, 1, -1), (0, -1, -1)],
         
            'Q' : [(1, 1, -1), (-1, 1, -1), (1, -1, -1), (-1, -1, -1),
                   (1, 0, -1), (-1, 0, -1), (0, 1, -1), (0, -1, -1)],
         
            'K' : [(1, 1, 1) , (1, 0, 1), (1, -1, 1),
                   (0, 1, 1), (0, -1, 1),
                   (-1, 1, 1), (-1, 0, 1), (-1, -1, 1)]
         }

def computeAttacked(board):
    
    for (row,col,piece) in board:
        if piece in mpGen:
            mpg = MultiplePositionGenerator(board, row, col, mpGen[piece])
        else:
            mpg = MultiplePositionGenerator(board, row, col, mpGen[piece.upper()])
        for (r,c) in mpg:
            board.setAttacked(r,c)
            
    return board.getFreeNonattacked()
        

from sys import stdin
if __name__ == '__main__':
    for l in stdin.read().splitlines():
        #print l
        b = Board()
        b.read(l)
        print (computeAttacked(b))
