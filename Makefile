MKDIR_P = mkdir -p
OUT_DIR = out

.PHONY: directory

all: directory program

directory: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

program:
	+$(MAKE) -C src

clean:
	+$(MAKE) clean -C src
