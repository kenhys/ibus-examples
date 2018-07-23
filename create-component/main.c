#include <ibus.h>
#include <glib.h>

typedef struct _IBusCreateComponentEngine IBusCreateComponentEngine;
typedef struct _IBusCreateComponentEngineClass IBusCreateComponentEngineClass;

struct _IBusCreateComponentEngine {
  IBusEngine parent;
};

struct _IBusCreateComponentEngineClass {
  IBusEngineClass parent;
};

static void	ibus_createcomponent_engine_class_init	(IBusCreateComponentEngineClass	*klass);
static void	ibus_createcomponent_engine_init		(IBusCreateComponentEngine		*engine);
static void	ibus_createcomponent_engine_destroy		(IBusCreateComponentEngine		*engine);
static gboolean
ibus_createcomponent_engine_process_key_event(IBusEngine             *engine,
                                         guint               	 keyval,
                                         guint               	 keycode,
                                         guint               	 modifiers);
G_DEFINE_TYPE(IBusCreateComponentEngine, ibus_createcomponent_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_CREATE_COMPONENT_ENGINE (ibus_createcomponent_engine_get_type())

GType   ibus_createcomponent_engine_get_type(void);

static void
ibus_createcomponent_engine_class_init (IBusCreateComponentEngineClass *klass)
{
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_createcomponent_engine_destroy;

  engine_class->process_key_event = ibus_createcomponent_engine_process_key_event;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;

static void
ibus_createcomponent_engine_init(IBusCreateComponentEngine *engine)
{
  IBusText *label = ibus_text_new_from_static_string("Create Component");
  IBusText *tips = ibus_text_new_from_static_string("");
  root = ibus_prop_list_new();
  submenu = ibus_prop_list_new();
  menu = ibus_property_new("InputMode",
                           PROP_TYPE_MENU,
                           label,
                           NULL,
                           NULL,
                           TRUE,
                           TRUE,
                           PROP_STATE_UNCHECKED,
                           submenu);
  g_object_ref_sink(menu);
  ibus_prop_list_append(root, menu);

  label = ibus_text_new_from_static_string("Menu A");
  IBusProperty *prop = ibus_property_new("Menu A KEY",
                                         PROP_TYPE_MENU,
                                         label,
                                         NULL,
                                         NULL,
                                         TRUE,
                                         TRUE,
                                         PROP_STATE_UNCHECKED,
                                         NULL);
  ibus_prop_list_append(submenu, prop);

  ibus_engine_register_properties((IBusEngine*)engine, root);
}

static void
ibus_createcomponent_engine_destroy(IBusCreateComponentEngine *engine)
{
  g_object_unref(menu);
  g_object_unref(root);
  ((IBusObjectClass *)ibus_createcomponent_engine_parent_class)->destroy((IBusObject *)engine);
}

static gboolean
ibus_createcomponent_engine_process_key_event(IBusEngine *engine,
                                         guint       keyval,
                                         guint       keycode,
                                         guint       modifiers)
{
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
  ibus_factory_add_engine(factory, "ibus-create-component", IBUS_TYPE_CREATE_COMPONENT_ENGINE);

  IBusComponent *component = ibus_component_new("com.example.IBus.CREATECOMPONENT",
                                                "CreateComponent for iBus",
                                                "1.0",
                                                "MIT",
                                                "Kentaro Hayashi",
                                                "https://github.com/kenhys/ibus-examples",
                                                "",
                                                "ibus-create-component");
  IBusEngineDesc *description = ibus_engine_desc_new("create-component",
                                                     "CreateComponent",
                                                     "Create Component (Japanese Input Method)",
                                                     "ja",
                                                     "MIT",
                                                     "Kentaro Hayashi",
                                                     "",
                                                     "default");
  ibus_component_add_engine(component, description);
  ibus_bus_register_component(bus, component);
  g_object_unref(component);

  ibus_main();

  return 0;
}
