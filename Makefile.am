AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -I $(srcdir)/streegp -Wall

IMPL_FILES = \
	impl/init.ipp

HEADER_FILES = \
	crossover.hpp \
	init.hpp \
	mutation.hpp \
	random.hpp \
	streegp.hpp \
	$(IMPL_FILES)

SOURCE_FILES = $(HEADER_FILES)

TESTS = test_init1 \
	test_mutation1

check_PROGRAMS = $(TESTS)

TEST_SOURCES = tests/macros.hpp tests/indiv.hpp
TEST_LIBS = -lstree

test_init1_SOURCES = tests/init1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_init1_LDADD = $(TEST_LIBS)

test_mutation1_SOURCES = tests/mutation1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_mutation1_LDADD = $(TEST_LIBS)
