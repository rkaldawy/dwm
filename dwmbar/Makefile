all: dwmbar

LIB_NAME = libdwmbar.so

SRC_ROOT = ./dwm-bar
LIB_ROOT = ./lib
INCLUDE_ROOT = ./include

LIB_PATH = $(SRC_ROOT)/$(LIB_NAME)
INCLUDE_PATH = $(SRC_ROOT)/dwmbar.h

$(LIB_PATH):
	$(MAKE) -C $(SRC_ROOT)

$(INCLUDE_PATH): $(LIB_PATH) ;

$(LIB_ROOT): $(LIB_PATH)
	mkdir -p $(LIB_ROOT); cp $(LIB_PATH) $(LIB_ROOT)

$(INCLUDE_ROOT): $(INCLUDE_PATH)
	mkdir -p $(INCLUDE_ROOT); cp $(INCLUDE_PATH) $(INCLUDE_ROOT)

dwmbar: $(LIB_ROOT) $(INCLUDE_ROOT)

clean:
	rm -rf $(LIB_ROOT) $(INCLUDE_ROOT); $(MAKE) -C $(SRC_ROOT) clean

install:
	$(MAKE) -C $(SRC_ROOT) install

.PHONY: install $(LIB_PATH)
