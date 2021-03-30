BASE = /usr/local/dx
include $(BASE)/lib_$(ARCH)/arch.mak

INCLUDES  = -I$(BASE)/include
DXLIB     = -L$(BASE)/lib_$(ARCH) -lDX
DXLIBLITE = -L$(BASE)/lib_$(ARCH) -lDXlite

mymodes: mymodes.c
		$(DXCC) $(INCLUDES) $(DXCFLAGS)  -c mymodes.c
		$(DXCC) $(INCLUDES) mymodes.o -o mymodes  

mycams:	mycams.c
		$(DXCC) $(INCLUDES) $(DXCFLAGS)  -c mycams.c
		$(DXCC) $(INCLUDES) mycams.o -o mymodes  

