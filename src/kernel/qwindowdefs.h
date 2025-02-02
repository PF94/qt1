/****************************************************************************
** $Id: qwindowdefs.h,v 2.26.2.11 1998/10/29 18:45:54 hanord Exp $
**
** Definition of general window system dependent functions, types and
** constants
**
** Created : 931029
**
** Copyright (C) 1992-1999 Troll Tech AS.  All rights reserved.
**
** This file is part of Qt Free Edition, version 1.45.
**
** See the file LICENSE included in the distribution for the usage
** and distribution terms, or http://www.troll.no/free-license.html.
**
** IMPORTANT NOTE: You may NOT copy this file or any part of it into
** your own programs or libraries.
**
** Please see http://www.troll.no/pricing.html for information about 
** Qt Professional Edition, which is this same library but with a
** license which allows creation of commercial/proprietary software.
**
*****************************************************************************/

#ifndef QWINDOWDEFS_H
#define QWINDOWDEFS_H

#ifndef QT_H
#include "qobjectdefs.h"
#endif // QT_H


// Class forward definitions

class QApplication;
class QPaintDevice;
class QPaintDeviceMetrics;
class QWidget;
class QWidgetMapper;
class QWindow;
class QDialog;
class QColor;
class QColorGroup;
class QPalette;
class QCursor;
class QPoint;
class QSize;
class QRect;
class QPointArray;
class QPainter;
class QRegion;
class QFont;
class QFontMetrics;
class QFontInfo;
class QPen;
class QBrush;
class QWMatrix;
class QPixmap;
class QBitmap;
class QMovie;
class QImage;
class QImageIO;
class QPicture;
class QPrinter;
class QAccel;
class QTimer;
class QClipboard;


// Widget list (defined in qwidgetlist.h)

#if defined(Q_TEMPLATEDLL)
class QWidgetList;
#else
class QListM_QWidget;
#define QWidgetList QListM_QWidget
#endif


// Window system setting

#if defined(_OS_MAC_)
#define _WS_MAC_
#elif defined(_OS_MSDOS_)
#define _WS_WIN16_
#error "Qt requires Win32 and does not work with Windows 3.x"
#elif defined(_WIN32_X11_)
#define _WS_X11_
#elif defined(_OS_WIN32_)
#define _WS_WIN32_
#elif defined(_OS_OS2_)
#define _WS_PM_
#elif defined(UNIX)
#define _WS_X11_
#endif

#if defined(_OS_DUCK_)
#undef _WS_X11_
#define _WS_POND_
#endif

#if defined(_WS_WIN16_) || defined(_WS_WIN32_)
#define _WS_WIN_
#endif


// Window system dependent definitions

#if defined(_WS_MAC_)
#endif // _WS_MAC_


#if defined(_WS_WIN_)

#if defined(_CC_BOR_) || defined(_CC_WAT_)
#define NEEDS_QMAIN
#endif

#define NO_STRICT

typedef void *HANDLE;
typedef void *HDC;
typedef void *HWND;
typedef HWND  WId;

typedef struct tagMSG MSG;


Q_EXPORT HANDLE qWinAppInst();
Q_EXPORT HANDLE qWinAppPrevInst();
Q_EXPORT int    qWinAppCmdShow();
Q_EXPORT HANDLE qt_display_dc();

enum WindowsVersion { WV_NT, WV_95, WV_98, WV_32s };

#if defined(QT_DLL) || defined(QT_MAKEDLL)
#define QT_BASEAPP
class QBaseApplication;
#define QApplication QBaseApplication
#endif

#endif // _WS_WIN16_ or _WS_WIN32_


#if defined(_WS_PM_)

typedef ulong HANDLE;
typedef ulong WId;
typedef ulong HAB;
typedef ulong HPS;
typedef ulong HDC;

typedef struct _QMSG   QMSG;
typedef struct _POINTL POINTL;
typedef struct _RECTL  RECTL;

HAB qPMAppInst();

#endif // _WS_PM_


#if defined(_WS_X11_)

typedef unsigned int  WId;
typedef unsigned int  HANDLE;
typedef struct _XDisplay Display;
typedef union  _XEvent XEvent;
typedef struct _XGC *GC;
typedef struct _XRegion *Region;

Q_EXPORT Display *qt_xdisplay();
Q_EXPORT int	 qt_xscreen();
Q_EXPORT WId	 qt_xrootwin();
Q_EXPORT GC	 qt_xget_readonly_gc( bool monochrome=FALSE );
Q_EXPORT GC	 qt_xget_temp_gc( bool monochrome=FALSE );

#endif // _WS_POND_

#if defined(_WS_POND_)

typedef unsigned int    WId;
typedef unsigned int    HANDLE;
typedef struct _PondMsg MSG;

#endif // _WS_POND_


#if defined(NEEDS_QMAIN)
#define main qMain
#endif


// Global platform-independent types and functions

typedef short QCOORD;				// coordinate type
const int QCOORD_MIN = -32768;
const int QCOORD_MAX =	32767;

typedef unsigned int QRgb;			// RGB triplet

Q_EXPORT char *qAppName();			// get application name


// Misc functions

typedef void (*CleanUpFunction)();
Q_EXPORT void qAddPostRoutine( CleanUpFunction );


Q_EXPORT void *qt_find_obj_child( QObject *, const char *, const char * );
#define CHILD(parent,type,name) \
	((type*)qt_find_obj_child(parent,#type,name))


// GUI styles

enum GUIStyle {
    MacStyle, // OBSOLETE
    WindowsStyle,
    Win3Style, // OBSOLETE
    PMStyle, // OBSOLETE
    MotifStyle
};


// Widget flags

typedef uint WFlags;

const uint WState_Created	= 0x00000001;	// widget state flags
const uint WState_Disabled	= 0x00000002;
const uint WState_Visible	= 0x00000004;
const uint WState_DoHide	= 0x00000008;
const uint WState_ClickToFocus	= 0x00000010;
const uint WState_TrackMouse	= 0x00000020;
const uint WState_BlockUpdates	= 0x00000040;
const uint WState_PaintEvent	= 0x00000080;

const uint WType_TopLevel	= 0x00000100;	// widget type flags
const uint WType_Modal		= 0x00000200;
const uint WType_Popup		= 0x00000400;
const uint WType_Desktop	= 0x00000800;

const uint WStyle_Customize	= 0x00001000;	// window style flags
const uint WStyle_NormalBorder	= 0x00002000;
const uint WStyle_DialogBorder	= 0x00004000;
const uint WStyle_NoBorder	= 0x00000000;
const uint WStyle_Title		= 0x00008000;
const uint WStyle_SysMenu	= 0x00010000;
const uint WStyle_Minimize	= 0x00020000;
const uint WStyle_Maximize	= 0x00040000;
const uint WStyle_MinMax	= WStyle_Minimize | WStyle_Maximize;
const uint WStyle_Tool		= 0x00080000;
const uint WStyle_Mask		= 0x000ff000;

const uint WCursorSet		= 0x00100000;	// misc widget flags
const uint WDestructiveClose	= 0x00200000;
const uint WPaintDesktop	= 0x00400000;
const uint WPaintUnclipped	= 0x00800000;
const uint WPaintClever		= 0x01000000;
const uint WConfigPending	= 0x02000000;
const uint WResizeNoErase	= 0x04000000;
const uint WRecreated		= 0x08000000;
const uint WExportFontMetrics	= 0x10000000;
const uint WExportFontInfo	= 0x20000000;
const uint WFocusSet		= 0x40000000;	// not used any more
const uint WState_TabToFocus	= 0x80000000;


class QFocusData;
#if defined(_WS_WIN_)
class QOleDropTarget;
#endif

// Extra QWidget data
//  - to minimize memory usage for members that are seldom used.

struct QWExtra {
    GUIStyle guistyle;				// GUI Style
    short    minw, minh;			// minimum size
    short    maxw, maxh;			// maximum size
    short    incw, inch;			// size increments
    char    *caption;				// widget caption
    char    *iconText;				// widget icon text
    QPixmap *icon;				// widget icon
#if defined(_WS_WIN_)
    HANDLE   winIcon;				// internal Windows icon
    QOleDropTarget *dropTarget;			// drop target
#endif
    QPixmap *bg_pix;				// background pixmap
    QFocusData *focusData;			// focus data (for TLW)
#if defined(_WS_X11_)
    void * xic;
#endif
    char     bg_mode;				// background mode

#if defined(_WS_X11_)
    uint dnd : 1;				// drop enable
#endif
    uint sizegrip : 1;				// size grip
    uint propagateFont: 2;
    uint propagatePalette: 2;
};


// Raster operations

enum RasterOp					// raster op/transfer mode
    { CopyROP, OrROP, XorROP, EraseROP,
      NotCopyROP, NotOrROP, NotXorROP, NotEraseROP, NotROP };


// Text formatting flags for QPainter::drawText and QLabel

const int AlignLeft	= 0x0001;		// text alignment
const int AlignRight	= 0x0002;
const int AlignHCenter	= 0x0004;
const int AlignTop	= 0x0008;
const int AlignBottom	= 0x0010;
const int AlignVCenter	= 0x0020;
const int AlignCenter	= AlignVCenter | AlignHCenter;

const int SingleLine	= 0x0040;		// misc. flags
const int DontClip	= 0x0080;
const int ExpandTabs	= 0x0100;
const int ShowPrefix	= 0x0200;
const int WordBreak	= 0x0400;
const int GrayText	= 0x0800;
const int DontPrint	= 0x1000;		// internal


// Image conversion flags

// The unusual ordering is caused by compatibility and default requirements.

const int ColorMode_Mask         = 0x00000003;
const int AutoColor              = 0x00000000;
const int ColorOnly              = 0x00000003;
const int MonoOnly               = 0x00000002;
//        Reserved               = 0x00000001;
const int AlphaDither_Mask       = 0x0000000c;
const int ThresholdAlphaDither   = 0x00000000;
const int OrderedAlphaDither     = 0x00000004;
const int DiffuseAlphaDither     = 0x00000008;
//        ReservedAlphaDither    = 0x0000000c;
const int Dither_Mask            = 0x00000030;
const int DiffuseDither          = 0x00000000;
const int OrderedDither          = 0x00000010;
const int ThresholdDither        = 0x00000020;
//        ReservedDither         = 0x00000030;
const int DitherMode_Mask        = 0x000000c0;
const int AutoDither             = 0x00000000;
const int PreferDither           = 0x00000040;
const int AvoidDither            = 0x00000080;


#endif // QWINDOWDEFS_H
