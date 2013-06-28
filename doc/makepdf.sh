#!/bin/sh
latex main.tex
bibtex main.aux
dvips main.dvi
ps2pdf main.ps
