======================
 libpnmio user manual
======================

+-------------------+----------------------------------------------------------+
| **Title**         | libpnmio (I/O PNM library)                               |
+-------------------+----------------------------------------------------------+
| **Author**        | Nikolaos Kavvadias 2012, 2013, 2014                      |
+-------------------+----------------------------------------------------------+
| **Contact**       | nikos@nkavvadias.com                                     |
+-------------------+----------------------------------------------------------+
| **Website**       | http://www.nkavvadias.com                                |
+-------------------+----------------------------------------------------------+
| **Release Date**  | 14 June 2014                                             |
+-------------------+----------------------------------------------------------+
| **Version**       | 1.0.0                                                    |
+-------------------+----------------------------------------------------------+
| **Rev. history**  |                                                          |
+-------------------+----------------------------------------------------------+
|        **v1.0.0** | 20-02-2014                                               |
|                   |                                                          |
|                   | First public release.                                    |
+-------------------+----------------------------------------------------------+
|        **v1.0.1** | 14-06-2014                                               |
|                   |                                                          |
|                   | Changed README to README.rst.                            |
+-------------------+----------------------------------------------------------+

.. _XnView: http://www.xnview.com
.. _Imagine: http://www.nyam.pe.kr/
.. _PNM: http://en.wikipedia.org/wiki/Netpbm_format
.. _PBM: http://netpbm.sourceforge.net/doc/pbm.html
.. _PGM: http://netpbm.sourceforge.net/doc/pgm.html
.. _PPM: http://netpbm.sourceforge.net/doc/ppm.html


1. Introduction
===============

The ``libpnmio`` library provides an implementation and API for reading 
and writing PNM_ (some times termed as Portable AnyMap) images. The PNM_ 
convention is collectively used to address PBM_ (Portable Bitmap), PGM_ 
(Portable Greymap) and PPM_ (Portable Pixmap) images.

The current version of ``libpnmio`` supports the ASCII variation of the 
PNM formats, however, it will be extended in order to support the 
corresponding binary formats. 

The library is accompanied by two test applications, namely ``randimg`` 
and ``doset``. ``randimg`` produces PBM/PGM/PPM image files filled with 
random data. ``doset`` generates a color illustration of the Mandelbrot set. 

Reference documentation for LIBPNMIO can be found in the ``/doc`` subdirectory 
in plain text, HTML and PDF form.


2. File listing
===============

The LIBPNMIO distribution includes the following files. 

+-----------------------+------------------------------------------------------+
| /libpnmio             | Top-level directory                                  |
+-----------------------+------------------------------------------------------+
| /bin                  | Executables directory (initially empty)              |
+-----------------------+------------------------------------------------------+
| /doc                  | Documentation directory                              |
+-----------------------+------------------------------------------------------+
| AUTHORS               | List of authors.                                     |
+-----------------------+------------------------------------------------------+
| LICENSE               | License agreement (modified BSD license).            |
+-----------------------+------------------------------------------------------+
| README.rst            | This file.                                           |
+-----------------------+------------------------------------------------------+
| README.html           | HTML version of README.rst.                          |
+-----------------------+------------------------------------------------------+
| README.pdf            | PDF version of README.rst.                           |
+-----------------------+------------------------------------------------------+
| rst2docs.sh           | Shell script for generating the documentation using  |
|                       | ``docutils``.                                        |
+-----------------------+------------------------------------------------------+
| VERSION               | Current version of the LIBPNMIO distribution.        |
+-----------------------+------------------------------------------------------+
| /lib                  | Compiled static library directory                    |
+-----------------------+------------------------------------------------------+
| /src                  | Source code directory                                |
+-----------------------+------------------------------------------------------+
| Makefile              | Makefile for compiling the library and generating    |
|                       | the executables.                                     |
+-----------------------+------------------------------------------------------+
| doset.c               | Generates a color visualization of the Mandelbrot    |
|                       | set.                                                 |
+-----------------------+------------------------------------------------------+
| pnmio.c               | Implementation of the ``libpnmio`` library in C.     |
+-----------------------+------------------------------------------------------+
| pnmio.h               | Header file (interface) of the ``libpnmio`` library. |
+-----------------------+------------------------------------------------------+
| randimg.c             | Random PBM/PGM/PPM image generator.                  |
+-----------------------+------------------------------------------------------+
| /test                 | Test script directory                                |
+-----------------------+------------------------------------------------------+
| run-doset.sh          | Bash script for running the Mandelbrot set example.  |
+-----------------------+------------------------------------------------------+
| run-randimg.sh        | Bash script for running the random image generator.  |
+-----------------------+------------------------------------------------------+


3. API description
==================

This section summarizes the intended functionality of the functions supported 
by the ``libpnmio`` application programming interface.

3.1. read_pbm_header
--------------------

| ``void read_pbm_header(FILE *f, int *img_xdim, int *img_ydim, int is_ascii);``

Read the header contents of a PBM (portable bit map) file. A PBM image file 
follows the format:

::

  P1
  <X> <Y>
  <I1> <I2> ... <IMAX>

A binary PBM image file uses P4 instead of P1 and the data values are  
represented in binary. 
Comment lines start with ``#``. 
``< >`` denote integer values (in decimal). For the PBM format, they can 
take only the 0 and 1 values.
``img_xdim`` and ``img_ydim`` correspond to ``X`` and ``Y``, respectively.
If ``is_ascii`` is 1, an ASCII PBM file is assumed; otherwise a binary PBM file 
is.


3.2. read_pgm_header
--------------------

| ``read_pgm_header(FILE *f, int *img_xdim, int *img_ydim, int *img_colors, int is_ascii);``

Read the header contents of a PGM (portable grey map) file. A PGM image file 
follows the format:

::

  P2
  <X> <Y> 
  <levels>
  <I1> <I2> ... <IMAX>

A binary PGM image file uses P5 instead of P2 and the data values are  
represented in binary.
Comment lines start with ``#``.
``< >`` denote integer values (in decimal).
``img_xdim``, ``img_ydim``, and ``img_colors`` correspond to ``X``, ``Y`` 
and ``levels``, respectively.
If ``is_ascii`` is 1, an ASCII PGM file is assumed; otherwise a binary PGM file 
is.

3.3. read_ppm_header
--------------------

| ``void read_ppm_header(FILE *f, int *img_xdim, int *img_ydim, int *img_colors, int is_ascii);``

Read the header contents of a PPM (portable pix map) file. A PPM image file 
follows the format:

::

  P3
  <X> <Y> 
  <levels>
  <R1> <G1> <B1> ... <RMAX> <GMAX> <BMAX>

A binary PPM image file uses P6 instead of P3 and the data values are  
represented in binary.
Comment lines start with ``#``. 
``< >`` denote integer values (in decimal).
``img_xdim``, ``img_ydim``, and ``img_colors`` correspond to ``X``, ``Y`` 
and ``levels``, respectively. Each color component, R, G, and B can take any 
value from 0 to levels.
If ``is_ascii`` is 1, an ASCII PPM file is assumed; otherwise a binary PPM file 
is.

3.4. read_pbm_data
------------------

| ``void read_pgm_data(FILE *f, int *img_in, int is_ascii);`` 

Read the data contents of a PBM (portable bit map) file.
``img_in`` denotes an array of integer values representing image data.
If ``is_ascii`` is 1, an ASCII PBM file is assumed; otherwise a binary PBM file 
is.

3.5. read_pgm_data
------------------

| ``void read_pgm_data(FILE *f, int *img_in, int is_ascii);``

Read the data contents of a PGM (portable grey map) file. 
``img_in`` denotes an array of integer values representing image data.
If ``is_ascii`` is 1, an ASCII PGM file is assumed; otherwise a binary PGM file 
is.

3.6. read_ppm_data
------------------

| ``void read_ppm_data(FILE *f, int *img_in, int is_ascii);``

Read the data contents of a PPM (portable pix map) file.
``img_in`` denotes an array of integer values representing image data.
If ``is_ascii`` is 1, an ASCII PPM file is assumed; otherwise a binary PPM file 
is.

3.7. write_pbm_file
-------------------

| ``void write_pbm_file(FILE *f, int *img_out, char *img_out_fname,`` 
| ``int x_size, int y_size, int x_scale_val, int y_scale_val, int linevals, int is_ascii);``

Write the contents of a PBM (portable bit map) file.
Data stored in array ``img_out`` are written to file ``f``. This file is 
assumed to be already opened under the name ``img_out_fname``. The 
image data represent an image of size ``x_size`` by ``y_size``. x-axis and 
y-axis scaling factors can be defined by ``x_scale_val`` and ``y_scale_val``.
``linevals`` determines the emission of newline characters for easier 
reading of the PBM file data.
If ``is_ascii`` is 1, an ASCII PBM file is assumed; otherwise a binary PBM file 
is.

3.8. write_pgm_file
-------------------

| ``void write_pgm_file(FILE *f, int *img_out, char *img_out_fname,`` 
| ``int x_size, int y_size, int x_scale_val, int y_scale_val, int img_colors,``
| ``int linevals, int is_ascii);``

Write the contents of a PGM (portable grey map) file.
Data stored in array ``img_out`` are written to file ``f``. This file is 
assumed to be already opened under the name ``img_out_fname``. The 
image data represent an image of size ``x_size`` by ``y_size``. x-axis and 
y-axis scaling factors can be defined by ``x_scale_val`` and ``y_scale_val``.
``img_colors`` determines the levels (0 to levels) for the common color 
component.
``linevals`` determines the emission of newline characters for easier 
reading of the PGM file data.
If ``is_ascii`` is 1, an ASCII PGM file is assumed; otherwise a binary PGM file 
is.

3.9. write_ppm_file
-------------------

| ``void write_ppm_file(FILE *f, int *img_out, char *img_out_fname,`` 
| ``int x_size, int y_size, int x_scale_val, int y_scale_val, int img_colors, int is_ascii);``

Write the contents of a PGM (portable grey map) file.
Data stored in array ``img_out`` are written to file ``f``. This file is 
assumed to be already opened under the name ``img_out_fname``. The 
image data represent an image of size ``x_size`` by ``y_size``. x-axis and 
y-axis scaling factors can be defined by ``x_scale_val`` and ``y_scale_val``.
``img_colors`` determines the levels (0 to levels) for the common color 
component. Each R-G-B triplet is printed to a separate line.
If ``is_ascii`` is 1, an ASCII PPM file is assumed; otherwise a binary PPM file 
is.


4. Build and setup
==================

In order to produce the static library, change directory to ``/src`` and 
run the Makefile as follows:

| ``make clean ; make``

This will produce the static library ``libpnmio.a`` and copy it to the 
``/lib`` subdirectory of the distribution. The executable files for the 
reference applications will also be generated and copied to the ``/bin``
subdirectory.

5. Run tests
------------

Two sample scripts are provided in the ``/test`` subdirectory. Change 
directory to ``/test`` and run the scripts as follows:

| ``cd test``
| ``./run-doset.sh``
| ``./run-randimg.sh``

PBM, PGM and PPM files can be directly visualized by using freeware image 
viewers such as XnView_ and Imagine_.


6. Prerequisities
=================

- Standard UNIX-based tools (tested with gcc-4.6.2 on MinGW/x64).
  
  * make
  * bash (shell)
  
  For this reason, MinGW (http://www.mingw.org) or Cygwin 
  (http://sources.redhat.com/cygwin) are suggested, since POSIX emulation 
  environments of sufficient completeness.
  

7. Contact
==========

You may contact me at:

|  Nikolaos Kavvadias <nikos@nkavvadias.com>
|  Independent Consultant
|  http://www.nkavvadias.com
|  Kornarou 12 Rd,
|  35100 Lamia, Fthiotis
|  Greece