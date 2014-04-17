SRC = main.c lex.yy.c y.tab.c node.c
all: bonsai

bonsai: ${SRC}
	cc -ggdb -o bonsai ${SRC}

lex.yy.c: bonsai.l
	flex bonsai.l

y.tab.c: parse.y
	bison -d -b y parse.y

clean:
	rm bonsai y.tab.h y.tab.c lex.yy.c
