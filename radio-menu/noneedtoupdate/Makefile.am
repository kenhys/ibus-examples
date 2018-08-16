libexec_PROGRAMS = ibus-engine-radiomenunoneedtoupdate

ibus_engine_radiomenunoneedtoupdate_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_radiomenunoneedtoupdate_CFLAGS = \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_radiomenunoneedtoupdate_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_radiomenunoneedtoupdate_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        radiomenunoneedtoupdate.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
        radiomenunoneedtoupdate.xml \
        $(NULL)
