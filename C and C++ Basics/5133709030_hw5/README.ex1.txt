Problems solved:
  1. Find the dimension of the matrix.
         1.1 Read the first line
              Create a char type array, use fgets to read the first line into the string. 
              Then use fseek to transfer the cursor back to the beginning of the file.
         1.2 Analyse the string
              Find the number of the space. The dimension should equal to (space +1).
  2. Calcultion.
             Use loops to calculate number by number.
  3.Structure 
         3.1 Structure can also be done by loop. I also use printf("\n"); properly to begin a new line to form a matrix. 
         3.2 Align
               By judging the digit of the numbers in the matrix we can align the matrix.


Problem remained:
     Align can't be written by a function because File *fp is hard to deal with.