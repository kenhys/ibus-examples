libexec_PROGRAMS = ibus-engine-simplemenu

ibus_engine_simplemenu_SOURCES = \
        engine.c engine.h \
        main.c \
        $(NULL)

ibus_engine_simplemenu_CFLAGS = \
        @IBUS_CFLAGS@ \
        $(NULL)

ibus_engine_simplemenu_LDFLAGS = \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        simple-menu.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        simple-menu.xml \
        $(NULL)
