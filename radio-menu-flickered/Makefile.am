libexec_PROGRAMS = ibus-engine-radiomenuflickered

ibus_engine_radiomenuflickered_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuflickered_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuflickered_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuflickered_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuflickered.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuflickered.xml \
        $(NULL)
