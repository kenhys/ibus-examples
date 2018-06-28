libexec_PROGRAMS = ibus-engine-changeinputmodesymbol

ibus_engine_changeinputmodesymbol_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_changeinputmodesymbol_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_changeinputmodesymbol_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_changeinputmodesymbol_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        changeinputmodesymbol.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        changeinputmodesymbol.xml \
        $(NULL)
