Before coding the game, I did some research to understand the logic of the game. According to the game rules, two of the tubes had to be empty at the beginning, otherwise the game could not be played. I asked the player to enter a minimum of 5 tubes. I defined a while loop to warn the user if the number of tubes is less than 5. Since a different coloured ball will be placed in each tube at the end of the game, I defined the number of colours as 2 less than the number of tubes.

I named each ball respectively, starting with the capital letter A and ending with Z.

After defining my two-dimensional array, I filled the balls into a one-dimensional array according to the number of colours. Here I arranged all the balls randomly. Then I placed these balls in my 2D array. Then I asked the user to make a move.

I defined functions that control errors, such as taking a ball from an empty tube or placing a ball into a full tube. I provided this control with if statements that test whether there is free space in the tube, starting from element 0.

To check that the balls were placed on the same coloured ball, I compared the numbers of the letters in the ASCII table.

To check that the game is over, I used an if-else statement that tests whether there are 2 empty tubes and whether the elements in the tubes are equal.
