libexec_PROGRAMS = ibus-engine-simplemenu

ibus_engine_simplemenu_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_simplemenu_CFLAGS = \
        @IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_simplemenu_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_simplemenu_LDADD = \
        @GTK_LIBS@ \
        $(NULL)

component_DATA = \
        simple-menu.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        simple-menu.xml \
        $(NULL)
