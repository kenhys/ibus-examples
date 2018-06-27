libexec_PROGRAMS = ibus-engine-hybrid

ibus_engine_hybrid_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_hybrid_CFLAGS = \
        @IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_hybrid_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_hybrid_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        hybrid.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        hybrid.xml \
        $(NULL)
