################################################################################################
# Makefile based on
# 	http://arantxa.ii.uam.es/~mcorella/teaching/mtp20506/Makefile
#	and
# 	https://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-for-gcc-on-linux
# Author: Borja Gil Perez, borja.gil@uam.es
################################################################################################
LIBS = -lm -pthread
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EXE=$(P1)
NAMES=stack generic_string palabra estado dynamic_node list configuracion_ap configuracion_apnd
DEPS=$(patsubst %,%.h,$(NAMES)) basic_types.h generic_collections_types.h
OBJ=$(patsubst %,%.o,$(NAMES))
# $ make
# $ make all

#all: p1 p2
all: p1

# $ make p1

#P1 = p1s1 p1s2
P1 = p1s2

p1: $(P1)
# $ make p2
#P2 = p2s1 p2s2
#p2: $(P2)

########################################################################
# P1
########################################################################
#main.o: main.c stack.h basic_types.h
#	$(CC) $(CFLAGS) -c $< -o $@
#stack.o: stack.c stack.h basic_types.h
#	$(CC) $(CFLAGS) -c $< -o $@
#generic_string.o: generic_string.c generic_string.h basic_types.h
#	$(CC) $(CFLAGS) -c $< -o $@	
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


#src2.o: src2.c header2.h
#	$(CC) $(CFLAGS) -c $< -o $@
# $ make p1s1
#p1s1: main.o src1.o src2.o
#p1s1: main.o stack.o generic_string.o
#	$(CC) $^ -Wall $(LIBS) -o $@

# $ make p1s2
p1s2: main.o $(OBJ)
	$(CC) $^ -Wall $(LIBS) -o $@
########################################################################
# P2
########################################################################
#src3.o: src3.c header2.h
#	$(CC) $(CFLAGS) -c $< -o $@
#src4.o: src4.c header1.h header2.h
#	$(CC) $(CFLAGS) -c $< -o $@
# $ make p2s1
#p2s1: src3.o src1.o
#	$(CC) $^ -Wall $(LIBS) -o $@
# $ make p2s2
#p2s2: src3.o src4.o src2.o
#	$(CC) $^ -Wall $(LIBS) -o $@
	
########################################################################
# Information and Clean
########################################################################
# $ make info
info:
	@echo
	@echo "<Autómatas y Lenguajes>, <Doble Grado>"
	@echo "<Codigo de la entrega>"
	@echo
	@echo "Autores:"
	@echo "	<Javier Gómez Martínez, Correo electronico>"
	@echo "	<Autor, Correo electronico>"
	@echo
	@echo "Ejecutables:"
	@echo "	all"
	@echo "		p1"
	@echo "			$(P1)"
	@echo "		p2"
	@echo "			$(P2)"
	@echo
# $ make clean
clean:
	@echo "Borrando objetos, ejecutables, etc."
	@rm -fr Doxyfile latex html
	@rm -f *~ *.o core $(P1) $(P2)
	
########################################################################
# Using utilities
########################################################################
# $ make astyle-c
astyle-c:
	@echo "Applying Artistic Style to C programming files."
	@astyle *.h *.c
# $ make doxygen
doxygen:
	@rm -fr Doxyfile latex html
	@doxygen -g
	@doxygen Doxyfile

valgrind:
	@valgrind --leak-check=full ./$(EXE)

zip:
	zip -r 1401_JavierGomez_CarlosLi_P1.zip *.c *.h Makefile
########################################################################
# Installation
########################################################################
# $ make dev-essential
dev-essential:
	@echo "Installing essential developer tools."
	sudo apt-get install astyle build-essential geany nemiver nmon terminator valgrind
	sudo apt-get install doxygen graphviz
# $ make lubuntu1404-custom
lubuntu1404-custom:
	@echo "Customizing Lubuntu 14.04"
	sudo apt-get purge abiword gnumeric
	sudo add-apt-repository ppa:indicator-brightness/ppa
	sudo add-apt-repository ppa:webupd8team/java
	sudo apt-get update
	sudo apt-get install language-selector-gnome libreoffice libreoffice-l10n-es lubuntu-restricted-extras thunderbird thunderbird-locale-es-es vlc
	sudo apt-get install indicator-brightness
	sudo apt-get install oracle-java8-installer && sudo apt-get install oracle-java8-set-default
	sudo apt-get autoremove && sudo apt-get autoclean
