# Target library
lib := libuthread.a
objs := queue.o uthread.o context.o sem.o preempt.o


## TODO: Phase 1
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -g

ifneq ($(V),1)
Q = @
endif

all: $(lib)

$(lib): $(objs)
	@echo "CC	$@"
	$(Q)ar rcs $@ $^

%.o: %.c %.h
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CLEAN"
	$(Q)rm -f $(lib) $(objs)
