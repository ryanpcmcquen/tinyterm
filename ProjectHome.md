# Tinyterm #

A terminal emulator written in C that uses [VTE](http://library.gnome.org/devel/vte/) as its back-end. Primary not intended to be overloaded with design options such as opacity, background image, font color etc., but with useful abilities which you won't find in other terminal implementations, e.g. access to the contents of the terminal buffer, multiple terminal sessions in one window and much more.

Tinyterm comes with no further windows. Instead constants are used to configure its behavior. The predefined ones should fit most of your needs anyway.

Note that Tinyterm is just a hobby project having a slow progress. Only a marginal number of features has been implemented yet. So don't expect too much and stay tuned for a release in the far future... ;-)

## Current state ##

  * Scrollbar on the right side
  * Copy selection with CTRL-SHIFT-C
  * Paste at cursor position with CTRL-SHIFT-V
  * Run selection via `xdg-open` with CTRL-SHIFT-X
  * Intelligent selection behavior: A double-click will mark a word/path/email/url

## Requirements ##

  * [CMake](http://www.cmake.org/) >= 2.6 (to do the build process)
  * The [VTE](http://library.gnome.org/devel/vte/) library (on a Debian-like system you may want to install it via `libvte-dev`)
  * Unix/Linux system (Windows is not supported)

## Standard Installation ##

  * It is recommended to create the sub-folder like `build` in the place where you have put Tinyterm in
  * Then change to your build-folder and run `cmake ..` from there
  * If no errors occured, you can do the normal `make` and `make install` (as root) procedure now to install Tinyterm