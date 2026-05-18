OBJS = main.o parsing.o isbuiltin.o
SRCS = $(OBJS:.o=.c)

myshell: $(OBJS)
	$(CC) -o $@ $(OBJS)
%.o: %.c
	$(CC) -c $<

clean:
	rm $(OBJS) myshell
