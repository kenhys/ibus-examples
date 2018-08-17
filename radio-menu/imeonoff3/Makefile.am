libexec_PROGRAMS = ibus-engine-radiomenuimeonoff3

ibus_engine_radiomenuimeonoff3_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuimeonoff3_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff3_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuimeonoff3_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuimeonoff3.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuimeonoff3.xml \
        $(NULL)
