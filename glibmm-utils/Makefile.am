
hh_sources = \
	glibmm-utils.h \
	date.h \
	exception.h \
	initializer.h \
	log-stream.h \
	log-stream-utils.h \
	option-utils.h \
	scope-logger.h \
	ustring.h

cc_sources = \
	date.cc \
	exception.cc \
	initializer.cc \
	log-stream.cc \
	option-utils.cc \
	scope-logger.cc \
	ustring.cc

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = glibmm-utils.pc

library_includedir = $(includedir)/glibmm-utils-@GTKMM_UTILS_API_VERSION@/glibmm-utils
library_include_HEADERS = $(hh_sources)

INCLUDES = \
	-I$(top_srcdir) \
	$(GLIBMM_CFLAGS) \
	$(LIBGTHREAD_CFLAGS)

lib_LTLIBRARIES = libglibmm-utils.la

libglibmm_utils_la_SOURCES = $(hh_sources) $(cc_sources)
libglibmm_utils_la_LIBADD = $(GLIBMM_LIBS) $(LIBGTHREAD_LIBS)
libglibmm_utils_la_LDFLAGS = -export-dynamic -fPIC -version-info @LIBGTKMM_UTILS_SO_VERSION@
