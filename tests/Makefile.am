TESTS = run-porg_tests.sh

check_PROGRAMS = test1 FindProcessByName_test

test1_SOURCE = test1
test1_LDADD = $(top_builddir)/lib/libporg.a -lpsapi -limagehlp -lntdll

FindProcessByName_test_SOURCE = FindProcessByName_test
FindProcessByName_test_LDADD = $(top_builddir)/lib/libporg.a -lpsapi -limagehlp -lntdll

AM_CPPFLAGS = -I$(top_srcdir)/include

EXTRA_DIST = run-porg_tests.sh test1.correct
