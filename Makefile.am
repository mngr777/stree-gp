AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -I $(srcdir)/streegp -Wall

IMPL_FILES = \
	streegp/impl/config.ipp \
	streegp/impl/init.ipp \
	streegp/impl/crossover.ipp \
	streegp/impl/mutation.ipp \
	streegp/impl/random.ipp \
	streegp/impl/results.ipp \
	streegp/impl/selection.ipp
HEADER_FILES = \
	streegp/config.hpp \
	streegp/context.hpp \
	streegp/crossover.hpp \
	streegp/individual.hpp \
	streegp/init.hpp \
	streegp/mutation.hpp \
	streegp/random.hpp \
	streegp/results.hpp \
	streegp/selection.hpp \
	streegp/streegp.hpp \
	$(IMPL_FILES)
SOURCE_FILES = $(HEADER_FILES) \
	src/config.cpp \
	src/individual.cpp

lib_LTLIBRARIES = libstreegp.la
libstreegp_ladir = $(includedir)
libstreegp_la_LIBADD = -lstree
nobase_libstreegp_la_HEADERS = $(HEADER_FILES)
libstreegp_la_SOURCES = $(SOURCE_FILES)

TESTS = test_init1 \
	test_mutation1 \
	test_crossover1 \
	test_config1

check_PROGRAMS = $(TESTS)

TEST_SOURCES = tests/macros.hpp
TEST_LIBS = -lstree libstreegp.la

test_init1_SOURCES = tests/init1.cpp $(TEST_SOURCES)
test_init1_LDADD = $(TEST_LIBS)

test_mutation1_SOURCES = tests/mutation1.cpp $(TEST_SOURCES)
test_mutation1_LDADD = $(TEST_LIBS)

test_crossover1_SOURCES = tests/crossover1.cpp $(TEST_SOURCES)
test_crossover1_LDADD = $(TEST_LIBS)

test_config1_SOURCES = tests/config1.cpp $(TEST_SOURCES)
test_config1_LDADD = $(TEST_LIBS)
