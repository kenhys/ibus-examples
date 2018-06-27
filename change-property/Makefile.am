libexec_PROGRAMS = ibus-engine-changeprop

ibus_engine_changeprop_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_changeprop_CFLAGS = \
        @IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_changeprop_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_changeprop_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        changeprop.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        changeprop.xml \
        $(NULL)
