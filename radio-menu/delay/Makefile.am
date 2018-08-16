libexec_PROGRAMS = ibus-engine-radiomenudelay

ibus_engine_radiomenudelay_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenudelay_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenudelay_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenudelay_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenudelay.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenudelay.xml \
        $(NULL)
