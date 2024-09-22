#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeGame(int num_tubes, char tubes[][4])
{
    int num_colors = num_tubes - 2; // Adjust the number of colors
    char ballColors[num_colors];
    char balls[num_colors * 4];

    // Initialize ball colors
    for (int i = 0; i < num_colors; ++i)
    {
        ballColors[i] = 'A' + i; // Use letters for colors (A, B, C, ...)
    }
    for (int i = 0; i < num_colors; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            balls[i*4 + j] = ballColors[i]; 
        }
    }

    //shuffle balls
    srand(time(NULL));
    int arraySize = sizeof(balls) / sizeof(char);
    

    for (int i = arraySize - 1; i > 0; --i) {
        // Generate a random index between 0 and i (inclusive)
        int k = rand() % (i + 1);

        // Swap array[i] and array[j]
        char temp = balls[i];
        balls[i] = balls[k];
        balls[k] = temp;
    }

    

    for (int i = 0; i < num_colors; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            tubes[i][j] = balls[i * 4 + j];
        }
    }

    for (int i = num_tubes - 1 ; i > num_tubes - 3; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            tubes[i][j] = '\0';
        }
        
    }
    
}

void displayGame(int num_tubes, char tubes[][4], int counter)
{
	printf("Moves: %d", counter);
    printf("\nCurrent state of the game:\n");

    for (int i = 0; i < num_tubes; ++i)
    {
        printf("Tube %d: ", i + 1);
        for (int j = 0; j < 4; ++j)
        {
        	if(tubes[i][j] != '\0'){
        		printf("%c ", tubes[i][j]);
			}
            
        }
        printf("\n");
    }
}

int isValidMove(int num_tubes, char tubes[][4], int fromTube, int toTube)
{
    // Check if tube indices are valid
    if (fromTube < 0 || fromTube >= num_tubes || toTube < 0 || toTube >= num_tubes)
    {
        return 0; // Invalid tube indices
    }

    // Check if the destination tube is full
    if (tubes[toTube][3] != '\0')
    {
        return 0; // The destination tube is full; the move is not valid.
    }

    // Check if the source tube is empty
    if (tubes[fromTube][0] == '\0')
    {
        return 0; // Source tube is empty; the user needs to select another tube.
    }

    return 1; // The move is valid.
}

void makeMove(char tubes[][4], int fromTube, int toTube)
{
    // Finding the last non-empty slot of the source tube
    int emptySlotForSource = 3;
    while (tubes[fromTube][emptySlotForSource] == '\0' && emptySlotForSource >= 0)
    {
        emptySlotForSource--; 
    }

    // Finding the last empty slot of the destination tube
    int emptySlotForDestination = 0;
    while (emptySlotForDestination < 4 && tubes[toTube][emptySlotForDestination] != '\0')
    {
        emptySlotForDestination++;
    }

	if(tubes[toTube][0] != '\0')
	{
	    // Check if the destination tube is not empty and the top ball does not match with the ball in the movement
	    if (tubes[fromTube][emptySlotForSource] != tubes[toTube][emptySlotForDestination - 1])
	    {
	        printf("Invalid move. Please try again.\n");
	        return;
	    }
	}
    // Move the ball from the source tube to the destination tube
    tubes[toTube][emptySlotForDestination] = tubes[fromTube][emptySlotForSource];
    tubes[fromTube][emptySlotForSource] = '\0';
}

int isGameFinalized(int num_tubes, char tubes[][4])
{
    int emptyTubeCount = 0;

    // Iterate through each tube
    for (int i = 0; i < num_tubes; ++i)
    {
       if(tubes[i][0] == '\0')
	   {
			emptyTubeCount++;
	   }
	   
	   else
        {
        	for(int j = 0; j < 3; ++j)
			{
				if(tubes[i][j] != tubes[i][j+1])
				{
					return 0;
				}
			}
        }
    }

    return (emptyTubeCount == 2); // Game is finalized
}

int main()
{
    int num_tubes = 0;
    int num_colors = 0;
    int counter = 0;

    printf("Enter the number of tubes (at least 5): ");
    scanf("%d", &num_tubes);

    while (num_tubes < 5)
    {
        system("cls");
        printf("\nTry Again: The number of tubes needs to be at least 5");
        printf("\nEnter the number of tubes: ");
        scanf("%d", &num_tubes);
    }
    char tubes[num_tubes][4];

    initializeGame(num_tubes, tubes);
    
    int fromTube, toTube;

    do
    {
    	if (isValidMove(num_tubes, tubes, fromTube - 1, toTube - 1))
		{
    		system("cls");
    		printf("\nMove successful!\n");
		}
		else
		{
			system("cls");
			printf("Invalid move. Please try again.\n");
		}
    	
        displayGame(num_tubes, tubes, counter);

        printf("Enter source tube index (1-%d): ", num_tubes);
        scanf("%d", &fromTube);

        printf("Enter destination tube index (1-%d): ", num_tubes);
        scanf("%d", &toTube);

        if (isValidMove(num_tubes, tubes, fromTube - 1, toTube - 1))
        {
            makeMove(tubes, fromTube - 1, toTube - 1);
            counter++;

            if (isGameFinalized(num_tubes, tubes))
            {
            	system("cls");
        		printf("Congratulations! You won the game with %d moves\n", counter);
        		displayGame(num_tubes, tubes, counter);
                break;
            }
        }
        else
        {
        	counter++;
        }

    } while (1);

    return 0;
}