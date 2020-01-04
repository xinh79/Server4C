SrcFiles=$(wildcard *.c)
ObjFiles=$(patsubst %.c,%.o,$(SrcFiles))
app:$(ObjFiles)
	gcc -o app -I./include $(ObjFiles)
%.o:%.c
	gcc -c $< -I./include
.PHONY:clean
clean:
	-@rm -f *.o
	@rm -f app
