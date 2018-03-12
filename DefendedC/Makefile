defendedcode : defendedCode.o sha256.o
	           gcc -pedantic -Wall -Wextra -Werror -o defendedcode defendedCode.o sha256.o
			   
defendedCode.o : defendedCode.c
		         gcc -pedantic -Wall -Wextra -Werror -c -g -MMD -MP -MF "defendedCode.o.d" -o defendedCode.o defendedCode.c
sha256.o : sha256.c sha256.h
		   gcc -pedantic -Wall -Wextra -Werror -c -g -MMD -MP -MF "sha256.o.d" -o sha256.o sha256.c
clean: 
	rm *.o
	rm *.od