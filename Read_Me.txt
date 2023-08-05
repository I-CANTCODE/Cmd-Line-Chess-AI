
Squares:
Numbered starting at 0, on bottom left from white
Increment by 1 to right
increment by 8 up



Move Notation:
An integer that indicates a move from one square to another

Given move n:
	destination square = n % 100
	origin square = ((n - n % 100) % 1000) / 100

Special Moves:
Indicated by adding x * 10000
x = :
1 - castle kingside
2 - castle queenside
3 - en passant
4 - pawn move 2
5 - promote to queen


Piece Values:
+ive = White, -ive = Black
1 = Pawn
2.5 = Knight
3 = Bishop
5 = Rook
9 = Queen
500 = King
