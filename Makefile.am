SUBDIRS = include src

if TESTS
  SUBDIRS += tests
endif

ACLOCAL_AMFLAGS = -I build/m4

dist-hook: changelog

changelog: $(top_srcdir)/.git/HEAD
	git log --stat > ChangeLog

doc: doxygen.conf
	doxygen doxygen.conf

