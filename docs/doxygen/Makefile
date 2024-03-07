SHELL := /bin/bash

SOURCE_FILES := $(shell find ../../modules -type f -name "stoneydsp_*.h" -or -name "stoneydsp_*.dox" | sed 's/ /\\ /g')

.PHONY: clean

build/juce_modules.dox: process_source_files.py $(SOURCE_FILES)
	python $< ../../modules build

doc/index.html: build/stoneydsp_modules.dox Doxyfile
	doxygen

clean:
	rm -rf build doc
