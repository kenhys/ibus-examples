libexec_PROGRAMS = ibus-engine-changeinputmodeicon

ibus_engine_changeinputmodeicon_SOURCES = \
        main.c \
        $(NULL)

ibus_engine_changeinputmodeicon_CFLAGS = \
        -DSAMPLE_A_ICON=\"$(pkgdatadir)/samplea.png\" \
        -DSAMPLE_B_ICON=\"$(pkgdatadir)/sampleb.png\" \
	@IBUS_CFLAGS@ \
        @GTK_CFLAGS@ \
        $(NULL)

ibus_engine_changeinputmodeicon_LDFLAGS = \
        @IBUS_LIBS@ \
        @GTK_LIBS@ \
        $(NULL)

ibus_engine_changeinputmodeicon_LDADD = \
        @GTK_LIBS@ \
        @IBUS_LIBS@ \
        $(NULL)

component_DATA = \
        changeinputmodeicon.xml \
        $(NULL)
componentdir = @datadir@/ibus/component

icon_DATA = \
        samplea.png \
        sampleb.png
icondir = $(pkgdatadir)

EXTRA_DIST = \
        changeinputmodeicon.xml \
        $(NULL)
