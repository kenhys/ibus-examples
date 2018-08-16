libexec_PROGRAMS = ibus-engine-radiomenuimeonoff2

ibus_engine_radiomenuimeonoff2_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuimeonoff2_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff2_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff2_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuimeonoff2.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuimeonoff2.xml \
        $(NULL)
