CFLAGS+=-I./include -I./msg -I./msg/facts -I./libthe/inc -Xlinker --allow-multiple-definition -lcurl -Wno-unused-command-line-argument
LDFLAGS+=--allow-multiple-definition
kitbot: main.o cmds.o irc.o kb.o
	${CC} -o $@ $^ ${CFLAGS}



msg/%.o: msg/%.c
	${CC} -c $^ ${CFLAGS} -o $@

msg/facts/%.o: msg/facts/%.c
	${CC} -c $^ ${CFLAGS} -o $@
	
src/%.o: src/%.c
	${CC} -c $^ ${CFLAGS} -o $@



ld_o=${LD} -r $^ ${LDFLAGS} -o $@

msg/facts.o: $(addsuffix .o, $(basename $(wildcard msg/facts/*.c)))
	${ld_o}

msg.o: $(addsuffix .o, $(basename $(wildcard msg/*.c)))
	${ld_o}

irc.o: src/irc.o src/queue.o
	${ld_o}

kb.o: src/kb.o
	${ld_o}

cmds.o: src/cmds.o irc.o kb.o libthe/libthe.a msg.o msg/facts.o
	${ld_o} # -Llibthe/libthe.a

main.o: src/main.o irc.o kb.o cmds.o
	${ld_o}

libthe/libthe.a: $(wildcard libthe/*/*.c)
	cd libthe; make all; cd ..
