#Recommend books to a reader by reading  evalution, of each book, from other users

File structure of the input

	First line has the number of books that exist in this file(1-60)

	Next lines: Books: "title", "author" // Each book in one line

	Next line: Number of users

	After books: "user" \n evalution for each book, a number from [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]

	End of user: "EndOfNames"

	Last line contains the name of the user


Algorithm "recAlgOptimal.c"

Makefile commands

	make: compiles code
	clear: deletes files
	make run: executes prog without args

Run with args, executable file is "recAlg", input file words.txt, save the output in myout1.txt

	./recAlg < words.txt > myout1.txt

Example with given files

	./recAlg < ./tests/functionEq/data1.txt > output1.txt

In folder tests there are files to test the algorithm

	Files with name "data?.txt" are input.

	Files with name "data?.std.txt" are the right output.

	Each folder has files to test extreme cases for different functions of the algorithm

Compare files

	diff -b myout1.txt stdout1.txt
