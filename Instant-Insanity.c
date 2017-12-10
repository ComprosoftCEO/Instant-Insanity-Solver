//Solve the insanity cube puzzle
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FACE_R 0
#define FACE_G 1
#define FACE_B 2
#define FACE_W 3

typedef struct {
	char color[2];
	char* string;
} color_pair;


typedef struct {
	color_pair pair[3];
} cube;

static const cube allCubes[] = {

	//Cube A
	{FACE_R,FACE_G,"R-G",
	 FACE_R,FACE_R,"R-R",
	 FACE_B,FACE_W,"B-W"},

	//Cube B
	{FACE_W,FACE_G,"W-G",
	 FACE_W,FACE_R,"W-R",
	 FACE_B,FACE_R,"B-R"},

	//Cube C
	{FACE_G,FACE_W,"G-W",
	 FACE_B,FACE_W,"B-W",
	 FACE_R,FACE_G,"R-G"},

	//Cube D
	{FACE_R,FACE_B,"R-B",
	 FACE_G,FACE_G,"G-G",
	 FACE_B,FACE_W,"B-W"}
};

int main(int argc, char* argv[]) {

	int current_spot = 0;
	int current_spot2 = 0;
	int index[4] = {0,0,0,0};	//What segment to ignore in the cubes
	int index2[4] = {0,0,0,0};	//Index for determining if the pairs work
	int count[4] = {0,0,0,0};	//How many of each segment exists
	int count2_A[4] = {0,0,0,0};
	int count2_B[4] = {0,0,0,0};
	int i, j, isGood, isGood2, spot;
	color_pair leftovers[4][2];			//After removing one pair, what are left?


	while(1) {

		for (i = 0; i < 4; i++) {count[i] = 0;}	//Reset counters

		//How many times does each number appear?
		for (i = 0; i < 4; i++) {
		spot = 0;
		for (j = 0; j < 3; j++) {		

			//Pair to ignore
			if (j != index[i]) {
				count[allCubes[i].pair[j].color[0]]+=1;
				count[allCubes[i].pair[j].color[1]]+=1;
	
				leftovers[i][spot] = allCubes[i].pair[j];
				spot+=1;
			}
		}}

	
		//We need EXACTLY 4 of each color
		isGood = 1;
		for (i = 0; i < 4; i++) {
			if (count[i] != 4) {isGood = 0; break;}
		}


		//We have the right number of colors.
		//  Now, does each side get EXACTLY 1 of each??
		if (isGood) {
			current_spot2 = 0;
			for (i = 0; i < 4; i++) {
				index2[i] = 0;
			}
		

			//There are 2 groups, A and B
			//	The colors in A need to match the colors in B
			//  However, we don't know which pair goes with the group,
			//    So try all combinations
			while(1) {

				for (i = 0; i < 4; i++) {
					count2_A[i] = 0;			
					count2_B[i] = 0;
				}

				//Total up groups A and G
				for (i = 0; i < 4; i++) {
				for (j = 0; j < 2; j++) {

					if (index2[i] == 0) {	//Group A
						count2_A[leftovers[i][0].color[j]] +=1;
						count2_B[leftovers[i][1].color[j]] +=1;
					} else {				//Group B
						count2_A[leftovers[i][1].color[j]] +=1;
						count2_B[leftovers[i][0].color[j]] +=1;
					}
				}}

				//Groups A and B should each have 2
				isGood2 = 1;
				for (i = 0; i < 4; i++) {
					
					if (count2_A[i] != 2 || count2_B[i] != 2) {
						isGood2 = 0; break;
					}
				}


				if (isGood2) {
					//Found it!!!
					printf("Not Visible:\t");
					for (i = 0; i < 4; i++) {
						printf("%s    ",allCubes[i].pair[index[i]].string);
					} printf("\n");

					printf("Permutation 1:\t");
					for (i = 0; i < 4; i++) {
						printf("%s    ",leftovers[i][index2[i]].string);
					} printf("\n");

					printf("Permutation 2:\t");
					for (i = 0; i < 4; i++) {
						printf("%s    ",leftovers[i][!index2[i]].string);
					} printf("\n");

					printf("------------------------------\n");
				}

			//Advance to the next index series
			next2:		
				index2[current_spot2]+=1;
				if (index2[current_spot2] == 2) {
					index2[current_spot2] = 0;
					current_spot2++;
					goto next2;
				} else {
					if (current_spot2 == 4) {break;}
					current_spot2 = 0;
				}
			}
		}

		
	//Advance to the next index series
	next:		
		index[current_spot]+=1;
		if (index[current_spot] == 3) {
			index[current_spot] = 0;
			current_spot++;
			goto next;
		} else {
			
			if (current_spot == 4) {break;}
			current_spot = 0;
		}

	}

	return 0;
}
