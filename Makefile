TARGET=main
CC ?= gcc
# direction source
BUI_DIR=./build
CRP_DIR=./crypto
BLC_DIR=./blockchain
TIM_DIR=./times
NET_DIR=./network
# source modules
CRP_SRC= md5.c sha256.c
BLC_SRC= block.c
TIM_SRC= datetime.c
MAIN_SRC= main.c
# object modules
CRP_OBJ= $(addsuffix .o,$(basename $(CRP_SRC)))
BLC_OBJ= $(addsuffix .o,$(basename $(BLC_SRC)))
TIM_OBJ= $(addsuffix .o,$(basename $(TIM_SRC)))
MAIN_OBJ= $(addsuffix .o,$(basename $(MAIN_SRC)))

CRP_PATH := $(foreach dir,$(CRP_SRC),$(wildcard $(CRP_DIR)/$(dir)))
BLC_PATH := $(foreach dir,$(BLC_SRC),$(wildcard $(BLC_DIR)/$(dir)))
TIM_PATH := $(foreach dir,$(TIM_SRC),$(wildcard $(TIM_DIR)/$(dir)))

CRP_INC := $(foreach dir,$(addsuffix .h,$(basename $(CRP_SRC))),$(wildcard $(CRP_DIR)/$(dir)))
BLC_INC := $(foreach dir,$(addsuffix .h,$(basename $(BLC_SRC))),$(wildcard $(BLC_DIR)/$(dir)))
TIM_INC := $(foreach dir,$(addsuffix .h,$(basename $(TIM_SRC))),$(wildcard $(TIM_DIR)/$(dir)))

$(TARGET): $(MAIN_OBJ) $(CRP_OBJ) $(BLC_OBJ) $(TIM_OBJ) $(CRP_INC) $(BLC_INC) $(TIM_INC)
	$(CC) $(BUI_DIR)/$< -o $(TARGET)

$(CRP_OBJ): $(CRP_PATH) 
	# $(CC) -c $< -o $(BUI_DIR)/$@
	echo $< $@ $(CRP_INC)

$(BLC_OBJ): $(BLC_PATH) $(BLC_INC)
	$(CC) -c $< -o $(BUI_DIR)/$@

$(TIM_OBJ): $(TIM_PATH) 
	$(CC) -c $< -o $(BUI_DIR)/$@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) -c -w $< -o $(BUI_DIR)/$@

clean:
	rm -f $(BUI_DIR)/*.o

# main: main.o sha256.o md5.o datetime.o block.o
# 	$(CC) $(BUI_DIR)/main.o $(BUI_DIR)/datetime.o $(BUI_DIR)/block.o $(BUI_DIR)/sha256.o $(BUI_DIR)/md5.o -o main

# sha256.o: ./crypto/sha256.c ./crypto/sha256.h
# 	$(CC) -c ./crypto/sha256.c -o $(BUI_DIR)/sha256.o

# md5.o: ./crypto/md5.c ./crypto/md5.h
# 	$(CC) -c ./crypto/md5.c -o $(BUI_DIR)/md5.o

# datetime.o: ./times/datetime.c ./times/datetime.h
# 	$(CC) -c ./times/datetime.c -o $(BUI_DIR)/datetime.o

# block.o: ./blockchain/block.c ./blockchain/block.h
# 	$(CC) -c ./blockchain/block.c -o $(BUI_DIR)/block.o

# main.o: main.c
# 	$(CC) -c main.c -o $(BUI_DIR)/main.o
# clean:
# 	rm -f $(BUI_DIR)/*.o