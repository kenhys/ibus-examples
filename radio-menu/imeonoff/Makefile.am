libexec_PROGRAMS = ibus-engine-radiomenuimeonoff

ibus_engine_radiomenuimeonoff_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuimeonoff_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuimeonoff.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuimeonoff.xml \
        $(NULL)
