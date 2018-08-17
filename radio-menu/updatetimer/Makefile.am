libexec_PROGRAMS = ibus-engine-radiomenuupdatetimer

ibus_engine_radiomenuupdatetimer_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenuupdatetimer_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenuupdatetimer_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenuupdatetimer_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenuupdatetimer.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenuupdatetimer.xml \
        $(NULL)
