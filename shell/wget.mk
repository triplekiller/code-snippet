BASE=https://dl.google.com/dl/brillo/bdk/latest
FILES=$(shell awk '{printf "%s.ext\n", $$1}' filelist.txt)
LOG=download.log

all: $(FILES)
	echo $(FILES)

%.ext:
#	wget -N -a $(LOG) $(BASE)/$@
	wget -N -q $(BASE)/$@

.PHONY: all
default: all
