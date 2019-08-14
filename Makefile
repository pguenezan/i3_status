CC        = g++
NAME      = i3status
CPPFLAGS  =
CFLAGS    = -O3 -lpthread
LDLIBS    =
RM        = rm -fv
MKDIR     = mkdir -p

MAIN      = main.cpp

SRC       = common_blocks.cpp  \
            spotify_block.cpp  \
            utils.cpp          \
            vpn_block.cpp      \
            prologin_block.cpp \

BUILD_DIR = build

all: $(NAME)

$(NAME): $(SRC)
	$(MKDIR) $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/$(NAME).o $(MAIN) $(SRC) $(CFLAGS) $(CPPFLAGS) \
	$(LDLIBS)

clean:
	$(RM) $(BUILD_DIR)/*.o
	rmdir $(BUILD_DIR)
