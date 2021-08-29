TARGET=main
CC ?=gcc
RM ?=rm
# flag compile
CFLAGS ?=-c -w 
CFLAGS_OUT ?=-o
# direction source
BUI_DIR=build
CRP_DIR=crypto
BLC_DIR=blockchain
TIM_DIR=times
NET_DIR=network
FS_DIR=fs
# source modules
FS_SRC= fs.c
CRP_SRC= md5.c sha256.c des.c crypto.c
BLC_SRC= block.c linkedlist.c blockchain.c
TIM_SRC= datetime.c
MAIN_SRC= main.c
# object modules
FS_OBJ= $(addsuffix .o,$(basename $(FS_SRC)))
CRP_OBJ= $(addsuffix .o,$(basename $(CRP_SRC)))
BLC_OBJ= $(addsuffix .o,$(basename $(BLC_SRC)))
TIM_OBJ= $(addsuffix .o,$(basename $(TIM_SRC)))
MAIN_OBJ= $(addsuffix .o,$(basename $(MAIN_SRC)))
# collect include header 
FS_INC := $(foreach dir,$(addsuffix .h,$(basename $(FS_SRC))),$(wildcard $(FS_DIR)/$(dir)))
CRP_INC := $(foreach dir,$(addsuffix .h,$(basename $(CRP_SRC))),$(wildcard $(CRP_DIR)/$(dir)))
BLC_INC := $(foreach dir,$(addsuffix .h,$(basename $(BLC_SRC))),$(wildcard $(BLC_DIR)/$(dir)))
TIM_INC := $(foreach dir,$(addsuffix .h,$(basename $(TIM_SRC))),$(wildcard $(TIM_DIR)/$(dir)))


$(TARGET): $(MAIN_OBJ) $(CRP_OBJ) $(BLC_OBJ) $(TIM_OBJ) $(FS_OBJ)
	@echo " CC		$@"
	@$(CC) $^ $(CFLAGS_OUT) $@

$(CRP_OBJ): $(CRP_INC)
	@echo " CC		$(CRP_DIR)/$(addsuffix .c,$(basename $@))"
	@$(CC) $(CFLAGS) $(CRP_DIR)/$(addsuffix .c,$(basename $@)) $(CFLAGS_OUT) $@

$(BLC_OBJ): $(BLC_INC)
	@echo " CC		$(BLC_DIR)/$(addsuffix .c,$(basename $@))"
	@$(CC) $(CFLAGS) $(BLC_DIR)/$(addsuffix .c,$(basename $@)) $(CFLAGS_OUT) $@

$(TIM_OBJ): $(TIM_INC)
	@echo " CC		$(TIM_DIR)/$(addsuffix .c,$(basename $@))"
	@$(CC) $(CFLAGS) $(TIM_DIR)/$(addsuffix .c,$(basename $@)) $(CFLAGS_OUT) $@

$(FS_OBJ): $(FS_INC)
	@echo " CC		$(FS_DIR)/$(addsuffix .c,$(basename $@))"
	@$(CC) $(CFLAGS) $(FS_DIR)/$(addsuffix .c,$(basename $@)) $(CFLAGS_OUT) $@

$(MAIN_OBJ): $(MAIN_SRC)
	@echo " CC		$<"
	@$(CC) $(CFLAGS) $< $(CFLAGS_OUT) $@

clean:
	@echo "CLEAN"
	@$(RM) $(CRP_OBJ)
	@$(RM) $(BLC_OBJ)
	@$(RM) $(TIM_OBJ)
	@$(RM) $(FS_OBJ)
	@$(RM) $(MAIN_OBJ)
	@$(RM) $(TARGET)
	@$(RM) temp/*