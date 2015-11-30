OBJ = Main.o phi_mult.o globals.o interp.o

Main.exe : $(OBJ)
		gcc -o  Main.exe $(OBJ) -lglut32 -lopenGL32 -lGLU32 

Main.o : Main.c globals.h  phi_mult.h interp.h
		gcc -c -O2 Main.c


phi_mult.o : phi_mult.c globals.h phi_mult.h interp.h
		gcc -c -O2 phi_mult.c

interp.o : interp.c globals.h interp.h
		gcc -c -O2 interp.c

globals.o  : globals.c globals.h
		gcc -c -O2 globals.c

clean : 
		rm Main.exe $(OBJ)
