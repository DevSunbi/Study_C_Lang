OBJS = main.o parsing.o isbuiltin.o isexcutable.o child_handler.o
SRCS = $(OBJS:.o=.c)
myshell: $(OBJS)
	$(CC) -o $@ $(OBJS)
%.o: %.c
	$(CC) -c $<
clean:
	rm $(OBJS) myshell
