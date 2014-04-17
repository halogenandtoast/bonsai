all: bonsai

bonsai: main.c lex.yy.c y.tab.c
	cc -o bonsai main.c lex.yy.c y.tab.c

lex.yy.c: bonsai.l
	flex bonsai.l

y.tab.c: parse.y
	bison -d -b y parse.y

clean:
	rm bonsai
