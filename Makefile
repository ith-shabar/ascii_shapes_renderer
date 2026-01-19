CC := gcc
EXECUTABLE := ascii_shapes_renderer

SOURCEDIR := src/
INCLUDEDIR := src/
BUILDDIR := build
INCLUDE := $(foreach D, $(INCLUDEDIR), -I$(D))
SOURCE := $(foreach S, $(SOURCEDIR), $(wildcard $(S)/*.c))

OBJECTS := $(patsubst $(SOURCEDIR)%.c, $(BUILDDIR)%.o, $(SOURCE))

CFLAGS := -Wall -Wextra -g -ffunction-sections -fdata-sections $(INCLUDE) 
CLINK := -lm

default: $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CLINK) -o $@ $^

$(BUILDDIR)/%.o: $(SOURCEDIR)%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	rm -rf $(OBJECTS)

delete: 
	rm $(EXECUTABLE) $(OBJECTS)
