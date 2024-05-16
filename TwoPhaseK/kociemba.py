# pip install RubikTwoPhase

import twophase.solver  as sv

cubestring = 'DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL'

moves = sv.solve(cubestring, 19, 2)

nummoves = moves[-4:-2] #the number of moves needed to solve the cube
print("num of moves: " + nummoves)
movesstring = moves[:-6] #substring the last part of the string which outputs the number of moves it will take
newmoves = "" #new formatted string

#map characters in moves to new string in the format of motornum + move direction
for character in movesstring:
    match character:
        case "U":
            newmoves += "1"
            continue
        case "R":
            newmoves += "2"
            continue
        case "F":
            newmoves += "3"
            continue
        case "D":
            newmoves += "4"
            continue
        case "L":
            newmoves += "5"
            continue
        case "B":
            newmoves += "6"
            continue
        case "1": #clockwise
            newmoves += "0 "
            continue
        case "2": #180degrees
            newmoves += "2 "
            continue
        case "3": #counterclockwise
            newmoves += "1 "
            continue
        case default:
            continue


print(newmoves)