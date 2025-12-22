#----------------------------------------------------------------------------
# File:		Makefile
# Author:	Tony Saveski, t_saveski@yahoo.com
#----------------------------------------------------------------------------
CC=ee-gcc
AS=ee-as
LD=ee-elf-ld
BMP2C=bmp2c

DEMO = demo2c

OBJ_DIR = obj
BMP_DIR = resources

CFLAGS = -Wall -W -EL -G0 -O0 -mips3 -nostdlib -DPS2_EE

BMP_SRC = hover.c message.c
C_SRC = gs.c g2.c $(DEMO).c $(BMP_SRC)
S_SRC = crt0.s ps2_asm.s dma_asm.s gs_asm.s

C_OBJ = $(addprefix $(OBJ_DIR)/, $(C_SRC:.c=.o))
S_OBJ = $(addprefix $(OBJ_DIR)/, $(S_SRC:.s=.o))

$(DEMO).elf: $(C_OBJ) $(S_OBJ)
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -Tlinkfile -o $(DEMO).elf $(C_OBJ) $(S_OBJ)

$(OBJ_DIR)/%.o: %.c
	@echo "-------------------------------------------------"
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s
	@echo "-------------------------------------------------"
	$(CC) -xassembler-with-cpp -c $(CFLAGS) $< -o $@

%.c: $(BMP_DIR)/%.bmp
	@echo "-------------------------------------------------"
	$(BMP2C) $< $(*F) > $@

clean:
	rm -f $(C_OBJ) $(S_OBJ) *.elf $(BMP_SRC)

hover.c: $(BMP_DIR)/hover.bmp
message.c: $(BMP_DIR)/message.bmp
