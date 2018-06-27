libexec_PROGRAMS = ibus-engine-createcomponent

ibus_engine_createcomponent_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_createcomponent_CFLAGS = \
        @IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_createcomponent_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_createcomponent_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        create-component.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        create-component.xml \
        $(NULL)
