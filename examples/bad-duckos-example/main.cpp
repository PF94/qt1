#include <qlist.h>
#include <qstring.h>
#include <stdio.h>

class Employee
{
public:
    Employee( const char *name, int salary ) { n=name; s=salary; }
    const char *name()   const               { return n; }
    int         salary() const               { return s; }
private:
    QString     n;
    int         s;
};

int main()
{
    printf( "QT %s testing - by ChazizGRKB\n", qVersion() );
    printf( "This port is a proof of concept and does not fully support any QT1 applications, "
            "especially not KDE1.\n\n");
    printf( "QList example (taken from the docs) below:\n" );

    QList<Employee> list;           // list of pointers to Employee
    list.setAutoDelete( TRUE );     // delete items when they are removed

    list.append( new Employee("Bill", 50000) );
    list.append( new Employee("Steve",80000) );
    list.append( new Employee("Ron",  60000) );

    Employee *emp;
    for ( emp=list.first(); emp != 0; emp=list.next() )
        printf( "%s earns %d\n", emp->name(), emp->salary() );

    return 1;
}