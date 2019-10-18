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
SOURCE_FILES = $(HEADER_FILES)

nobase_include_HEADERS = $(HEADER_FILES)

TESTS = test_init1 \
	test_mutation1 \
	test_crossover1 \
	test_config1

check_PROGRAMS = $(TESTS)

TEST_SOURCES = tests/macros.hpp
TEST_LIBS = -lstree

test_init1_SOURCES = tests/init1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_init1_LDADD = $(TEST_LIBS)

test_mutation1_SOURCES = tests/mutation1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_mutation1_LDADD = $(TEST_LIBS)

test_crossover1_SOURCES = tests/crossover1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_crossover1_LDADD = $(TEST_LIBS)

test_config1_SOURCES = tests/config1.cpp $(TEST_SOURCES) $(SOURCE_FILES)
test_config1_LDADD = $(TEST_LIBS)
