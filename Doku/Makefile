BASE = dhpaper

LATEX    = pdflatex
BIBTEX   = bibtex
GLOSSARY = makeglossaries

all:
	$(MAKE) pdf
	$(MAKE) bib
	$(MAKE) glossary
	$(MAKE) pdf
	$(MAKE) pdf

pdf:
	$(LATEX) $(BASE).tex

bib:
	$(BIBTEX) $(BASE)

glossary:
	$(GLOSSARY) $(BASE)

clean:
	rm *.aux *.acn *.acr *.alg *.bbl *.blg *.glg *.glo *.gls *.ist *.lof *.log *.lol *.lot *.run.xml *.toc *-blx.bib

build:
	$(MAKE) all
	$(MAKE) clean

rebuild:
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) clean