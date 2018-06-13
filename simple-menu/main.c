#include <ibus.h>
#include <glib.h>

typedef struct _IBusSimpleMenuEngine IBusSimpleMenuEngine;
typedef struct _IBusSimpleMenuEngineClass IBusSimpleMenuEngineClass;

struct _IBusSimpleMenuEngine {
  IBusEngine parent;
};

struct _IBusSimpleMenuEngineClass {
  IBusEngineClass parent;
};

static void	ibus_simplemenu_engine_class_init	(IBusSimpleMenuEngineClass	*klass);
static void	ibus_simplemenu_engine_init		(IBusSimpleMenuEngine		*engine);
static void	ibus_simplemenu_engine_destroy		(IBusSimpleMenuEngine		*engine);
static gboolean
ibus_simplemenu_engine_process_key_event(IBusEngine             *engine,
                                         guint               	 keyval,
                                         guint               	 keycode,
                                         guint               	 modifiers);
G_DEFINE_TYPE(IBusSimpleMenuEngine, ibus_simplemenu_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_SIMPLE_MENU_ENGINE (ibus_simplemenu_engine_get_type())

GType   ibus_simplemenu_engine_get_type(void);

static void
ibus_simplemenu_engine_class_init (IBusSimpleMenuEngineClass *klass)
{
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_simplemenu_engine_destroy;

  engine_class->process_key_event = ibus_simplemenu_engine_process_key_event;
}

static void
ibus_simplemenu_engine_init(IBusSimpleMenuEngine *engine)
{
}

static void
ibus_simplemenu_engine_destroy(IBusSimpleMenuEngine *engine)
{
  ((IBusObjectClass *)ibus_simplemenu_engine_parent_class)->destroy((IBusObject *)engine);
}

static gboolean
ibus_simplemenu_engine_process_key_event(IBusEngine *engine,
                                         guint       keyval,
                                         guint       keycode,
                                         guint       modifiers)
{
    if (modifiers & IBUS_RELEASE_MASK)
        return FALSE;

    return FALSE;
}

int main(int argc, char *argv[])
{
  ibus_init();

  IBusBus *bus = ibus_bus_new();
  g_object_ref_sink(bus);

  g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_quit), NULL);

  IBusFactory *factory = ibus_factory_new(ibus_bus_get_connection(bus));
  g_object_ref_sink(factory);
  ibus_factory_add_engine(factory, "ibus-simple-menu", IBUS_TYPE_SIMPLE_MENU_ENGINE);

  ibus_bus_request_name(bus, "com.example.IBus.SIMPLEMENU", 0);

  ibus_main();
}
