# LFA_HW2-Grammar-acceptance
It takes the input from a file describing a regular grammar of the form  
  
S 2 aA dE  
A 2 aB aS  
B 1 bC   
C 2 bD bB  
D 2 cD -  
E 1 -  

WHERE:  
->'-' represent the lambda,the empty word  
->Capital letters are the states of the machine  
->Digits are the number of transitions of a node  
->LowerCaseLetter-UpperCaseLetter is a transitions
  
And words from a file
