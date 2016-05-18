# SimpleUI

The project aims at different renderers of W3C XForms-1.0 subset.


###Links
* [Copyright](COPYING.md) - BSD
* [Authors](AUTHORS.md)


###Dependencies
####From Sources
#####Mandatory
* [libxml2](http://www.xmlsoft.org/) - for XML parsing
* [Qt](http://www.qt.io) - Qt Toolkit
* [Gtk](http://www.gtk.org) - Gtk Toolkit
* [FLTK](http://www.fltk.org) - FLTK Toolkit



###Building
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install

####Build Flags
... are typical cmake flags like CMAKE\_C\_FLAGS to tune compilation.

* CMAKE\_INSTALL\_PREFIX to install into paths and so on. Use on the command 
  line through -DCMAKE\_INSTALL\_PREFIX=/my/path .
* LIB\_SUFFIX - allows to append a architecture specific suffix like 
  LIB\_SUFFIX=64 for 64bit RedHat style Linux systems.
