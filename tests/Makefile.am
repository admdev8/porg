TESTS = run-porg_tests.sh

check_PROGRAMS = test1

test1_SOURCE = test1
test1_LDADD = $(top_builddir)/lib/libporg.a -lpsapi -limagehlp

AM_CPPFLAGS = -I$(top_srcdir)/include

EXTRA_DIST = run-porg_tests.sh test1.correct
