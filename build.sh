CPP=g++
YACC=bison
LEX=flex
MAIN=Chatto
COMPILE_FLAGS=

# 编译parser.y生成parser.cpp和parser.hpp
${YACC} -d -o parser.cpp parser.y

# 编译lex.l生成lex.cpp
${LEX} -o lex.cpp lex.l

# 编译lex.cpp parser.cpp生成lex.o parser.o
${CPP} ${COMPILE_FLAGS} -c parser.cpp lex.cpp

# 编译IR.cpp Sentence.cpp生成IR.o Sentence.o
${CPP} -c IR.cpp Sentence.cpp

# 编译链接IR.o Sentence.o parser.o lex.o生成可执行文件
${CPP} IR.o Sentence.o parser.o lex.o -o ${MAIN}

# 删除中间文件
rm parser.cpp parser.o lex.cpp lex.o IR.o Sentence.o