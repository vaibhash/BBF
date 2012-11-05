##  
## 
##	Author : vaibhavs@flux.utah.edu
##	Description: makefile for bloom project 
##
##
###############################################################################
ODIR =	Objects
OBJS =	$(addprefix $(ODIR)/, RollOverHash.o Bloom.o BloatedBloom.o ReadHaystack.o ReadNeedleToBloom.o Input.o)
	
	VPATH = RollOverHash:Bloom:BloatedBloom:ReadNeedleToBloom:Include:ReadHaystack:Input
CC = g++
DEBUG = -g -fpermissive
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

.phoney: clean

all: $(OBJS) bloatedbloom



bloatedbloom : $(OBJS) 
	$(CC) $(LFLAGS) Interface/Interface.c $(OBJS) -o bloatedbloom

$(ODIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@



clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.gch $(ODIR)/*~ 

tar:
	tar zcfv bloatedbloom.tar.gz RollOverHash BloatedBloom Bloom ReadHaystack ReadNeedleToBloom RollOverHash Include Input  Makefile
