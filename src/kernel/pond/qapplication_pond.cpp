#include "qglobal.h"
#include "qapplication.h"
#include "qwidget.h"
#include "qobjectlist.h"
#include "qobjectdict.h"
#include "qwidgetlist.h"
#include "qwidgetintdict.h"
#include "qbitarray.h"
#include "qpainter.h"
#include "qpixmapcache.h"
#include "qdatetime.h"
#include "qkeycode.h"
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <errno.h> 
#include <libpond/Window.h>

void qt_init( int *argcptr, char **argv )
{
  // Misc. initialization

    QColor::initialize();
    QFont::initialize();
    QCursor::initialize();
    QPainter::initialize();
}

void qt_cleanup()
{
    QPixmapCache::clear();
    QPainter::cleanup();
    QCursor::cleanup();
    QFont::cleanup();
    QColor::cleanup();
}