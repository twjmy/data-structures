For this question, I didn't make an optimal solution.
I won't give you the actual output. I'll give you only the output length of my algorithm.
However, I'll upload the actual output after this work is due.

Please believe me that I will not deliberately avoid the weakness of my algorithm. I'll have a fair competition with all of you.

test1: DESPACITO
actual output: ++++.+.>--------.---.>+.++.<<++++.>++++.-----.
length: 46

test2: QWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWERQWER
length: 218

test3: ABCDEFGHIJKLMNOPQRSTUVWXYZYXWVUTSRQPONMLKJIHGFEDCBA
length: 102

test4: OEODOCOHONOGOSOAOXOZOHOVOVODODOOYOWOAOVOJODOAOFOJNODOCO
length: 213

test5: FGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGOFGO
length: 226

test6: HEY I JUST MET YOU AND THIS IS CRAZY BUT HERES MY NUMBER SO CALL ME MAYBE ITS HARD TO LOOK RIGHT AT YOU BABY BUT HERES MY NUMBER SO CALL ME MAYBE HEY I JUST MET YOU AND THIS IS CRAZY BUT HERES MY NUMBER SO CALL ME MAYBE AND ALL THE OTHER BOYS TRY TO CHASE ME BUT HERES MY NUMBER SO CALL ME MAYBE
length: 1075

test7: GOD KEEP MY HEAD ABOVE WATER I LOSE MY BREATH AT THE BOTTOM COME RESCUE ME ILL BE WAITING IM TOO YOUNG TO FALL ASLEEP DONT LET ME DROWN DROWN DROWN DONT LET ME DONT LET ME DONT LET ME DROWN DONT LET ME DROWN DROWN DROWN
length: 933


When scoring, I'll sum up all the lengths of your output and compare with my algorithm.
Use test1 to test7 as an example:
46 + 218 + 102 + 213 + 226 + 1075 + 933 = 2813 is the standard.
You'll get:
0% if your output length is >11252.
10% if your output length is between 5627 to 11252.
20% if your output length is between 3095 to 5626. (2813*1.1 = 3094.3)
30% if your output length is between 2673 to 3094.
40% if your output length is <2673.