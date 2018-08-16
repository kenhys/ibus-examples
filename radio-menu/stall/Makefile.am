libexec_PROGRAMS = ibus-engine-radiomenustall

ibus_engine_radiomenustall_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenustall_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenustall_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenustall_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenustall.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenustall.xml \
        $(NULL)
