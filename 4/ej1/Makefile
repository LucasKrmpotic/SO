CC = gcc
ODIR = obj
SDIR = src
OUT  = servidor

HARDSRC = $(SDIR)/hardware.c $(SDIR)/hardware.h
COMSRC = $(SDIR)/comunicaciones.c $(SDIR)/comunicaciones.h $(SDIR)/hardware.h
SOFTSRC = $(SDIR)/servidor.c $(SDIR)/servidor.h $(SDIR)/interfaz.h $(SDIR)/comunicaciones.h
 
_OBJS = servidor.o comunicaciones.o hardware.o 

OBJS = $(patsubst %, $(ODIR)/%,$(_OBJS))

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $(OBJS)

clean:
	rm -f $(ODIR)/*.o $(OUT)

$(ODIR)/hardware.o: $(HARDSRC)
	$(CC) -o $(ODIR)/hardware.o -c $(SDIR)/hardware.c

$(ODIR)/comunicaciones.o: $(COMSRC)
	$(CC) -o $(ODIR)/comunicaciones.o -c $(SDIR)/comunicaciones.c

$(ODIR)/servidor.o: $(SOFTSRC)
	$(CC) -o $(ODIR)/servidor.o -c $(SDIR)/servidor.c 
