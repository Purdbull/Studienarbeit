@echo off
rem Delete all .aux files, delete intermediate dhpaper.* files.
rem This script is separate in case of errors, so the user may inspect intermediately generated files.
del *.aux
del dhpaper.acn
del dhpaper.acr
del dhpaper.alg
del dhpaper.bbl
del dhpaper.blg
del dhpaper.glg
del dhpaper.glo
del dhpaper.gls
del dhpaper.ist
del dhpaper.lof
del dhpaper.log
del dhpaper.lol
del dhpaper.lot
del dhpaper.run.xml
del dhpaper.toc
del dhpaper-blx.bib