libexec_PROGRAMS = ibus-engine-radiomenufromarray

ibus_engine_radiomenufromarray_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenufromarray_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenufromarray_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenufromarray_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenufromarray.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenufromarray.xml \
        $(NULL)
