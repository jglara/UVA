from sys import stdin

class BowlingScorer:
    def __init__(self):
        self.rolls = []

    def addScore(self, score):
        if score == 'X':
            self.rolls.append(10)
        elif score == '/':
            self.rolls.append( 10 - self.rolls[-1] )
        elif score.isdigit():
            self.rolls.append(int(score))

    @staticmethod
    def calcScore(scores):
        bs = BowlingScorer()

        for score in scores:
            bs.addScore(score)

#        print bs.rolls 
        points = 0
        frame = 1
        firstRoll = True
        for i in range(0,len(scores)):
            if scores[i] == 'X':
                points += bs.rolls[i]
                if frame < 10: points += bs.rolls[i+1] + bs.rolls[i+2]
                frame += 1
                firstRoll = True
            elif scores[i] == '/':
                points += bs.rolls[i]
                if frame < 10: points += bs.rolls[i+1]
                frame += 1
                firstRoll = True
            else:
                points += bs.rolls[i]
                if firstRoll:
                    firstRoll = False
                else:
                    frame += 1
                    firstRoll = True
#            print points
        return points
    
    @staticmethod
    def readScore(line):
        if line == "Game Over":
            return None
        else:
            return [c for c in line if c != ' ']

    @staticmethod
    def printScores(afile):
        for line in afile.read().splitlines():
            scores = BowlingScorer.readScore(line)
            if scores:
                points = BowlingScorer.calcScore(scores)
                print(points)
                

def calcBowlingScore(scores, finalScore, frame, bonus):
    #print("sc={}, fs={}, f={}, b={}".format(scores, finalScore, frame, bonus))
    if len(scores) == 0:
        return finalScore
    else:
        roll1= scores.pop(0)
        if roll1 == 'X':
            finalScore += 10
            
            if bonus == 3:
                finalScore += 20
                bonus -= 2
            elif bonus > 0:
                finalScore += 10
                bonus -= 1
                    
            roll2= '0'
        else:
            points1 = int(roll1)
            if len(scores)>0:
                roll2 = scores.pop(0)
            else:
                roll2 = '0'
                
            if roll2 == '/':
                points2 = 10 - points1
            else:
                points2 = int(roll2)
                
            finalScore += points1 + points2
            
            if bonus==1:
                finalScore += points1
            elif bonus==2:
                finalScore += points1 + points2
            elif bonus==3:
                finalScore += points1*2 + points2
            bonus = 0
                                
        if frame <10:
            if roll1 == 'X':
                bonus += 2
            elif roll2 == '/':
                bonus += 1
                
        frame += 1
        return calcBowlingScore(scores,finalScore, frame, bonus)
                
    

if __name__ == "__main__":
#    print ("score = {}".format(BowlingScorer.calcScore("X"*12)))
#    print ("score = {}".format(BowlingScorer.calcScore("101/22X33X1/3/X12")))
    #BowlingScorer.printScores(stdin)
    for line in stdin.read().splitlines():
        if line == "Game Over":
            break
        scores = [c for c in line if c != ' ']
        print(calcBowlingScore(scores, 0, 1, 0))

