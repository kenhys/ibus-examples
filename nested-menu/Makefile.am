libexec_PROGRAMS = ibus-engine-nestedmenu

ibus_engine_nestedmenu_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_nestedmenu_CFLAGS = \
        @IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_nestedmenu_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_nestedmenu_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        nestedmenu.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        nestedmenu.xml \
        $(NULL)
