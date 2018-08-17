libexec_PROGRAMS = ibus-engine-radiomenuupdatebytimer

ibus_engine_radiomenuupdatebytimer_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuupdatebytimer_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuupdatebytimer_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuupdatebytimer_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuupdatebytimer.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuupdatebytimer.xml \
        $(NULL)
