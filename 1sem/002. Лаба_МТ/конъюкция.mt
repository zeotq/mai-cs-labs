0, ,<,0
0,0,0,1
0,1,1,1

1,0, ,2 // последний бит б = 0
1,1, ,20 // последний бит б = 1

// для 0

2, ,>,3 
3,0,>,3
3,1,>,3
3, , ,4
4, ,0,5 // запись результата
5,0,<,5 
5,1,<,5
5, ,<,6 // пробел между результатом и б

6, ,<,8 // когда слово б пусто
6,0,<,7
6,1,<,7
7,0,<,7
7,1,<,7
7, ,<,8

8, ,<,8
8,0, ,9
8,1, ,9

9, ,>,9
9,0,0,10
9,1,1,10
10,0,>,10
10,1,>,10
10, ,>,11
11, ,>,11
11,0,<,12
11,1,<,12
12, , ,0

// для 1

20, ,>,23 
23,0,>,23
23,1,>,23
23, , ,24
24, ,1,25 // запись предварительного результата
25,0,<,25 
25,1,<,25
25, ,<,26 // пробел между результатом и б

26, ,<,28 // когда слово б пусто
26,0,<,27
26,1,<,27
27,0,<,27
27,1,<,27
27, ,<,28

28, ,<,28
28,0, ,29 // последний разряд а = 0 -> заменить предварительный ответ на 0
28,1, ,9 // последний разряд а = 1 -> предварительный ответ верен

29, ,>,29
29,0,0,210
29,1,1,210
210,0,>,210
210,1,>,210
210, ,>,211
211, ,>,211
211,0,<,212
211,1,0,212
212,0,<,0
212, , ,0
