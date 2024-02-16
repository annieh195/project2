# Target library
lib := libuthread.a
objs := queue.o uthread.o context.o sem.o preempt.o


## TODO: Phase 1
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -g

all: $(lib)

$(lib): $(objs)
	@echo "CC	$@"
	@ar rcs $@ $^

%.o: %.c %.h
	@echo "CC	$@"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CLEAN"
	@rm -f $(lib) $(objs)
