/****************************************************************************
** $Id: qdir.h,v 2.9.2.1 1998/08/19 16:02:35 agulbra Exp $
**
** Definition of QDir class
**
** Created : 950427
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

#ifndef QDIR_H
#define QDIR_H

#ifndef QT_H
#include "qstrlist.h"
#include "qfileinfo.h"
#endif // QT_H

#if defined(_OS_DUCK_)
#warning "needs a lot of non-implemented things"
#else

typedef Q_DECLARE(QListM,QFileInfo)	    QFileInfoList;
typedef Q_DECLARE(QListIteratorM,QFileInfo) QFileInfoListIterator;


class Q_EXPORT QDir
{
public:
    enum FilterSpec { Dirs	    = 0x001,
		      Files	    = 0x002,
		      Drives	    = 0x004,
		      NoSymLinks    = 0x008,
		      All	    = 0x007,
		      TypeMask	    = 0x00F,

		      Readable	    = 0x010,
		      Writable	    = 0x020,
		      Executable    = 0x040,
		      RWEMask	    = 0x070,
		      Modified	    = 0x080,
		      Hidden	    = 0x100,
		      System	    = 0x200,
		      AccessMask    = 0x3F0,
		      DefaultFilter = -1 };

    enum SortSpec   { Name	    = 0x00,
		      Time	    = 0x01,
		      Size	    = 0x02,
		      Unsorted	    = 0x03,
		      SortByMask    = 0x03,
		      DirsFirst	    = 0x04,
		      Reversed	    = 0x08,
		      IgnoreCase    = 0x10,
		      DefaultSort   = -1 };

    QDir();
    QDir( const char *path, const char *nameFilter = 0,
	  int sortSpec = Name | IgnoreCase, int filterSpec = All );
    QDir( const QDir & );
   ~QDir();
    QDir       &operator=( const QDir & );
    QDir       &operator=( const char *path );

    void	setPath( const char *path );
    const char *path()		const;
    QString	absPath()	const;
    QString	canonicalPath()	const;

    QString	dirName() const;
    QString	filePath( const char *fileName,
			  bool acceptAbsPath = TRUE ) const;
    QString	absFilePath( const char *fileName,
			     bool acceptAbsPath = TRUE ) const;

    static QString convertSeparators( const char *pathName );

    bool	cd( const char *dirName, bool acceptAbsPath = TRUE );
    bool	cdUp();

    const char *nameFilter() const;
    void	setNameFilter( const char *nameFilter );
    FilterSpec filter() const;
    void	setFilter( int filterSpec );
    SortSpec sorting() const;
    void	setSorting( int sortSpec );

    bool	matchAllDirs() const;
    void	setMatchAllDirs( bool );

    uint	count() const;
    const char *operator[]( int ) const;

    const QStrList *entryList( int filterSpec = DefaultFilter,
			       int sortSpec   = DefaultSort  ) const;
    const QStrList *entryList( const char *nameFilter,
			       int filterSpec = DefaultFilter,
			       int sortSpec   = DefaultSort   ) const;

    const QFileInfoList *entryInfoList( int filterSpec = DefaultFilter,
					int sortSpec   = DefaultSort  ) const;
    const QFileInfoList *entryInfoList( const char *nameFilter,
					int filterSpec = DefaultFilter,
					int sortSpec   = DefaultSort   ) const;

    static const QFileInfoList *drives();

    bool	mkdir( const char *dirName,
			      bool acceptAbsPath = TRUE ) const;
    bool	rmdir( const char *dirName,
			      bool acceptAbsPath = TRUE ) const;

    bool	isReadable() const;
    bool	exists()   const;
    bool	isRoot()   const;

    bool	isRelative() const;
    void	convertToAbs();

    bool	operator==( const QDir & ) const;
    bool	operator!=( const QDir & ) const;

    bool	remove( const char *fileName,
			      bool acceptAbsPath = TRUE );
    bool	rename( const char *name, const char *newName,
			      bool acceptAbsPaths = TRUE  );
    bool	exists( const char *name,
			      bool acceptAbsPath = TRUE );

    static char separator();

    static bool setCurrent( const char *path );
    static QDir current();
    static QDir home();
    static QDir root();
    static QString currentDirPath();
    static QString homeDirPath();
    static QString rootDirPath();

    static bool match( const char *filter, const char *fileName );
    static QString cleanDirPath( const char *dirPath );
    static bool isRelativePath( const char *path );

private:
    void	init();
    bool	readDirEntries( const QString &nameFilter,
				int FilterSpec, int SortSpec  );

    QString	dPath;
    QStrList   *fList;
    QFileInfoList *fiList;
    QString	nameFilt;
    FilterSpec	filtS;
    SortSpec	sortS;
    uint	dirty	: 1;
    uint	allDirs : 1;
};


inline const char *QDir::path() const
{
    return dPath.data();
}

inline const char *QDir::nameFilter() const
{
    return (const char *) nameFilt;
}

inline QDir::FilterSpec QDir::filter() const
{
    return filtS;
}

inline QDir::SortSpec QDir::sorting() const
{
    return sortS;
}

inline bool QDir::matchAllDirs() const
{
    return allDirs;
}

inline bool QDir::operator!=( const QDir &d ) const
{
    return !(*this == d);
}


#endif // QDIR_H
#endif