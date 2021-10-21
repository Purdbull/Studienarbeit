# LaTeX-Package `dhpaper` and Template for DHBW Papers

This is a LaTeX template for DHBW reports and project papers.
The formatting for the cover page and necessary packages and configurations for the papers are in the `dhpaper.sty` file, the rest are examples for the use of every package.

List of key LaTeX files:

* `dhpaper.bib` - Bibliography file for use with BibLaTeX.
* `dhpaper.sty` - Style file for proper fonts, cover page, etc.
* `dhpaper.tex` - Main project file, contains configuration for the cover page, table of contents, content listings, and includes constituent chapters.
* `body.tex` - Contains usage examples for images, code, tables (with captions), and acronyms and glossary terms.
* `glossary.tex` - Defines abbreviations, acronyms, and glossary terms.

System-specific compilation scripts:

* `compile.bat` - Windows batch file for compilation of `dhpaper.tex`, including BibTeX bibliography and `glossaries` package (requires a Perl installation).
* `cleanup.bat` - Cleans up intermediately generated files. Packed as a separate file from `compile.bat` for troubleshooting purposes.
* `Makefile` - works under Linux and Windows; requires a Perl installation.

---

## Makefile Options

* `make all` - Build the complete PDF with bibliography and glossaries, keep all intermediate files.
* `make bib` - Build the BibTeX files.
* `make glossary` - Creates the glossary and abbreviation list files.
* `make pdf` - Builds the basic PDF output file with `pdfLaTeX`.
* `make clean` - Removes all intermediate files.
* `make build` - Builds the complete PDF with bibliography and glossaries, then deletes all intermediate files.
* `make rebuild` - Cleans the directory, then reruns the `build` procedure.

---

## How to use this LaTeX Document

The file `dhpaper.tex` and the `dhpaper.sty` style file is the basis of this document.
The style file defines the package `dhpaper`, which contains all package dependencies necessary for the title page, code listings, figures, bibliography, and glossaries.
The style file also defines a basic code highlighting style, which can be extended and modified as needed for specific programming languages.
For details see the style file itself and documentation of the `listings` package.
Usage examples for every package are given in `body.tex`, which represents the "Hauptteil" chapter in the sample document.

To create the title page, simply enter your information (adding company and DHBW logos) into the `dhpaper.tex` file in the title page segment.
The `dhpaper` package adds the following creation commands:

* `\maketitlepage` - Creates the title page with company and school logos, title of the report, and student and company information.
The following information is displayed (and should be set accordingly):

  * `\projecttitle` - Title of the report.
  * `\projecttype` - Type of the report ("Praxisbericht", "Projektarbeit", "Studienarbeit", "Bachelorarbeit", etc.).
  * `\projectauthor` - Name of the report's author.
  * `\studentid` - The student's DHBW identification number (*Matrikelnummer*).
  * `\companyname` - Name of the student's company.
  * `\companylocation` - Location (town or city) of the student's company.
  * `\companylogo` - Filename of the company's logo.
  * `\companyadvisor` - Name of the student's advisor at the company.
  * `\schoolname` - Name of the student's school.
  * `\schoollogo` - Logo of the student's school.
  * `\schooladvisor` - Name of the student's advisor at the school.
  * `\deadline` - Deadline for handing in the report.
  * `\duration` - Timeframe of when the report (or the work described therein) was completed.
  * `\degreetype` - Type of degree program (Bachelor's, Master's, PhD, etc.).
  * `\subject` - Subject of the student's degree program.
  * `\courseid` - Number or description of the student's degree program.

* `\makestatement` - Statement of originality of the report, i. e. "this is my own work".
* `\makenda` - Confidentiality statement that may be required by the student's company.

Lists that aren't required (e.g. if you don't have any tables or code listings) should be commented out.
If a list is removed at the front, be sure to set the page counter (`\setcounter{page}{x}`) before the appendix accordingly.

You may add your work to the following files, or create your own and include them in `dhpaper.tex`:

* `intro.tex` - Introduction, preliminary remarks, overview of the project.
* `foundations.tex` - Theoretical foundations of the work presented.
* `body.tex` - Actual, "own" work done in the course of the report's subject matter.
* `conclusion.tex` - Summary and discussion of the report's results.

* `dhpaper.bib` - Registry of sources and references used in the report.
* `glossary.tex` - List of abbreviations, acronyms, and glossary terms with their definitions.
