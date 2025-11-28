# file structure
## generic project

```
.vscode/         project-specific setup for VSCode
bin/             executable files & firmware images
    app.exe
doc/             manuals & Obsidian snapshots
    app/
        app.md   title page from project's Obsidian dir
lib/
	app.ini      application initialisation script
tmp/             temporary files
    app.history  REPL commands history
ref/             reference code from other apps & libs (incl. legacy)
etc/             misc configurations & scripts
    app.service  systemd service for app
```

## C++

```
lib/
	app.ini
	component1/      C++ library 1 (component design)
	    inc/
	    src/
	component2/
```
```
lib/
inc/
    app.hpp
    libc.hpp
    main.hpp
    watch.hpp
    net.hpp
    repl.hpp
    syntax.hpp
src/
src/libc.cpp
src/watch.cpp
src/net.cpp
src/app.cpp
src/repl.cpp
src/syntax.cpp
src/main.cpp
	app.cpp
	app.lex
	app.yacc
	app.ragel
tmp/
    app.history  REPL commands history
ref/             reference code from other apps & libs (incl. legacy)
```

[[RTOS/bib]]
## [[em/cross|cross]]

```
hw/
    inc/
        cross.hpp
        hw.hpp
    src/
    pc/                 generic x86_64 pc/server
        inc/
            pc.hpp
        src/
            pc.cpp
        pc.mk
        pc.cmake
cpu/
    inc/
        cpu.hpp
    src/
        cpu.cpp
    i5/                 generic x86_64 cpu
        inc/
            i5.hpp
        src/
            i5.cpp
        i5.mk
        i5.cmake
arch/
os/
	inc/
	    os.hpp
	src/
	    main.cpp
	linux/              desktop/server Linux
	    inc/
	        linux.hpp
	    src/
	        linux.cpp
	    linux.mk
	    linux.cmake
```

## [[legas]]

```
legas/ -> ~/legas/
	legas.ml
```
