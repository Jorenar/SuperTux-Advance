SuperTux Advance - Installation
===============================

To compile SuperTux you need a copy of DevKitPro and libgba, which are
both available at https://www.devkitpro.org

After you have unzipped it both, just set the environment variable
DEVKITPRO to the directory where you unzipped it and run `make`

In the top level dir of SuperTux Advance. Currently some of the .raw
files are not generated automatically, so some manual work with
`png2raw` is needed to get a clean compile.
