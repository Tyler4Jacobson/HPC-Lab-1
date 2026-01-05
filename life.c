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
    // TODO:  write code for this

} // periodicBuffer

/*
 *  newLife - compute the "life" for cell at [row][col]
 *  		using data from oldboard and putting the
 *  		result (the next generation) into the newboard
 */
void
newLife(char **newboard, char **oldboard, int r, int c)
{
    // TODO:  write code for this
    // This code is just a place holder and should be replaced:
    newboard[r][c] = oldboard[r][c];

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
	    system("sleep 0.05");	// TODO: delete for speed
	 }

	 // TODO: periodicBuffer(board[(gen & 1)]);

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

