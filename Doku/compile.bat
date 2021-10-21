@echo off
rem Compiles the document completely, including references, bibliography, and glossaries/acronyms.
pdflatex dhpaper.tex
bibtex dhpaper
makeglossaries dhpaper

rem Call pdflatex twice after completing bibtex and makeglossaries, see also BibTeX and glossaries package documentation.
pdflatex dhpaper.tex
pdflatex dhpaper.tex
