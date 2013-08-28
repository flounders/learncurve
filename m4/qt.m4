# Checking for Qt capability

AC_DEFUN([BR_QT_DIR],
[ AC_MSG_CHECKING(QT4.1 directory)
QTDIR=xxx
AC_ARG_WITH([qt-dir],
		AS_HELP_STRING([--with-qt-dir=/path/to/Qt-4.1.0],
				[to specify the path to the Qt-4.1.0 directory.]),
		[QTPATHS="$withval"],
		[QTPATHS="/usr/local/Trolltech/Qt-4.1.0 /c/qt/4.1.0 /usr"])

for x in $QTPATHS; do
	if test -d $x ; then
		QTDIR="$x"
	fi
done

if test $QTDIR = xxx ; then
	AC_MSG_ERROR(Could not locate QT 4.1)
fi

AC_MSG_RESULT($QTDIR)
])

AC_DEFUN_ONCE([BR_QT_LIBS],
[
host=`uname -a`
case $host in 
	Linux*)
		AC_MSG_NOTICE(Linux detected)
		AC_PATH_XTRA
		QTLIBS="-Wl,-rpath,$QTDIR/lib -L$QTDIR/lib -lQtGui -lQtOpenGL -lQtCore -lQtWebKit"
		QTLIBS="$QTLIBS $X_LIBS -lX11 -lXext -lXmu -lXt -lXi $X_EXTRA_LIBS -lGLU -lGL -lpthread"
		QTINC="-I$QTDIR/include -I$QTDIR/include/QtGui -I$QTDIR/include/QtCore -I$QTDIR/include/QtOpenGL -I$QTDIR/include/QtWebKit"
		QTINC="$QTINC $X_CFLAGS -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB"
		QTBIN="$QTDIR/bin"
		;;
esac
AC_MSG_NOTICE($QTLIBS)
AC_MSG_NOTICE($QTINC)
LIBS="$LIBS $QTLIBS"
INCLUDES="$INCLUDES $QTINC"
PATH="$PATH:$QTBIN"
CXXFLAGS="$CXXFLAGS $QTINC"
])

AC_DEFUN_ONCE([BR_QT_TEST],
[
cat > myqt.h << EOF
#include <QObject>
class Test : public QObject
{
Q_OBJECT
public:
  Test() {}
  ~Test() {}
public slots:
  void receive() {}
signals:
  void send();
};
EOF

cat > myqt.cpp << EOF
#include "myqt.h"
#include <QApplication>
int main( int argc, char **argv )
{
  QApplication app( argc, argv );
  Test t;
  QObject::connect( &t, SIGNAL(send()), &t, SLOT(receive()) );
}
EOF

AC_MSG_CHECKING(does moc work?)
bnv_try_1="moc-qt4 myqt.h -o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_1)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(moc doesn't work)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile moc_myqt.cpp?)
bnv_try_2="$CXX -c $CXXFLAGS -o moc_myqt.o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_2)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile moc_myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile myqt.cpp?)
bnv_try_3="$CXX $QTINC -c $CXXFLAGS -o myqt.o myqt.cpp"
AC_TRY_EVAL(bnv_try_3)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I link against QT?)
nv_try_4="$CXX $LIBS -o myqt myqt.o moc_myqt.o"
AC_TRY_EVAL(bnv_try_4)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't link)
fi
AC_MSG_RESULT(yes)

AC_MSG_CHECKING(for mkoctfile)
AC_TRY_EVAL(mkoctfile)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(mkoctfile is not in the path)
fi
AC_MSG_RESULT(yes)
rm -f moc_myqt.cpp myqt.h myqt.cpp myqt.o myqt moc_myqt.o

])

