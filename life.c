/*
 * Conway's game of Life
 *
 */
#include <stdio.h>
#include <stdlib.h>

char **board[2];
int ROWSIZ, COLSIZ;

/*
 *  Fill the edges of the board with data to make a
 *  periodic buffer ("wraparound")
 */
void
periodicBuffer(char **theboard)		// theboard - a 2D array
{
	// Top
	for (int i=0; i < COLSIZ; i++) {
		theboard[0][i] = theboard[ROWSIZ-2][i];
	}
	// Bottom
	for (int i=0; i < COLSIZ; i++) {
		theboard[ROWSIZ-1][i] = theboard[1][i];
	}
	// Left
	for (int i=0; i < ROWSIZ; i++) {
		theboard[i][0] = theboard[i][COLSIZ-2];
	}
	// Right
	for (int i=0; i < ROWSIZ; i++) {
		theboard[i][COLSIZ-1] = theboard[i][1];
	}
} // periodicBuffer

/*
 *  newLife - compute the "life" for cell at [row][col]
 *  		using data from oldboard and putting the
 *  		result (the next generation) into the newboard
 */
void
newLife(char **newboard, char **oldboard, int r, int c)
{
	// RULES:
	// 1) Alive -> Dead with <2 neighbors
	// 2) Alive -> Alive with 2 or 3 neighbors
	// 3) Alive -> Dead with >3 neighbors
	// 4) Dead -> Alive with =3 neighbors

	// Sum neighbors
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1) continue;
			if (oldboard[r-1+i][c-1+j]) sum++;
		}
	}

	if (oldboard[r][c]) { 			// Alive
		if (sum < 2) newboard[r][c] = 0;
		if (sum == 2 || sum == 3) newboard[r][c] = 1;
		if (sum > 3) newboard[r][c] = 0;
	} else if (!oldboard[r][c]) { 	// Dead
		if (sum == 3) newboard[r][c] = 1;
		else newboard[r][c] = 0;
	}

} // newLife

int
main(int argc, char **argv)
{
    int row,col;
    int gen, genOut, period;

    if (argc > 1) {
	genOut = atoi(argv[1]);
	period = atoi(argv[2]);
    } else {
	printf ("usage: life generations output-frequency < infile\n");
	exit(-1);
    }

    // read inputfile and init array
    loadlife();
    fprintf(stderr, "load complete\n");

    for(gen=0; gen < genOut; gen++) {
		if (period > 0 && gen%period == 0) {
			displayBoard(period, board[gen&1]);
			//system("sleep 0.05");	// TODO: delete for speed
		}

		periodicBuffer(board[(gen & 1)]);

		for (row=1; row < ROWSIZ-1; row++) {
			for (col=1; col < COLSIZ-1; col++) {
			if (gen & 1) {
				newLife(board[0], board[1], row, col);
			} else {
				newLife(board[1], board[0], row, col);
			}
			} // next col
		} // next row

    } // next gen

    if (period == 0 || gen%period != 0) {
		displayBoard(period, board[1-(gen&1)]);  // show last board updated
		if (period > 0) {
			printf("gen:%d\n", gen);
		}
    }

} // main

