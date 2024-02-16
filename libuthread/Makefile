# Target library
lib := libuthread.a
objs := queue.o uthread.o context.o sem.o preempt.o


## TODO: Phase 1
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD
CFLAGS	+= -g

ifneq ($(V),1)
Q = @
endif

all: $(lib)

deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

$(lib): $(objs)
	@echo "CC	$@"
	@ar rcs $@ $^

%.o: %.c 
	@echo "CC	$@"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CLEAN"
	@rm -f $(lib) $(objs) $(deps)
