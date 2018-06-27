#include <ibus.h>
#include <glib.h>

typedef struct _IBusHybridEngine IBusHybridEngine;
typedef struct _IBusHybridEngineClass IBusHybridEngineClass;

struct _IBusHybridEngine {
  IBusEngine parent;
};

struct _IBusHybridEngineClass {
  IBusEngineClass parent;
};

static void ibus_hybrid_engine_class_init(IBusHybridEngineClass	*klass);
static void ibus_hybrid_engine_init(IBusHybridEngine *engine);
static void ibus_hybrid_engine_destroy(IBusHybridEngine *engine);
static gboolean
ibus_hybrid_engine_process_key_event(IBusEngine *engine,
                                     guint keyval,
                                     guint keycode,
                                     guint modifiers);
G_DEFINE_TYPE(IBusHybridEngine, ibus_hybrid_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_HYBRID_ENGINE (ibus_hybrid_engine_get_type())

GType ibus_hybrid_engine_get_type(void);

static void
ibus_hybrid_engine_class_init(IBusHybridEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_hybrid_engine_destroy;

  engine_class->process_key_event = ibus_hybrid_engine_process_key_event;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;

static void
ibus_hybrid_engine_init(IBusHybridEngine *engine)
{
  g_debug(G_STRFUNC);
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
ibus_hybrid_engine_destroy(IBusHybridEngine *engine)
{
  g_debug(G_STRFUNC);
  g_object_unref(menu);
  g_object_unref(root);
  ((IBusObjectClass *)ibus_hybrid_engine_parent_class)->destroy((IBusObject *)engine);
}

static gboolean
ibus_hybrid_engine_process_key_event(IBusEngine *engine,
                                         guint       keyval,
                                         guint       keycode,
                                         guint       modifiers)
{
    return FALSE;
}

static gboolean execute_by_ibus = FALSE;
static const GOptionEntry options[] =
{
    { "ibus", 'i', 0, G_OPTION_ARG_NONE, &execute_by_ibus, "Component is executed by IBus", NULL },
    { NULL },
};
  
int main(int argc, char *argv[])
{
  GError *error = NULL;
  GOptionContext *context = g_option_context_new("- IBus Hybrid engine");
  g_option_context_add_main_entries(context, options, "ibus-hybrid");

  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_print("Failed to parse options: %s\n", error->message);
    g_error_free(error);
    return -1;
  }

  ibus_init();

  IBusBus *bus = ibus_bus_new();
  g_object_ref_sink(bus);

  g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_quit), NULL);

  IBusFactory *factory = ibus_factory_new(ibus_bus_get_connection(bus));
  g_object_ref_sink(factory);
  ibus_factory_add_engine(factory, "ibus-hybrid", IBUS_TYPE_HYBRID_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.HYBRID", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.HYBRID",
                                                  "Hybrid for iBus",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-hybrid");
    IBusEngineDesc *description = ibus_engine_desc_new("hybrid",
                                                       "Hybrid",
                                                       "Hybrid (Japanese Input Method)",
                                                       "ja",
                                                       "MIT",
                                                       "Kentaro Hayashi",
                                                       "",
                                                       "default");
    ibus_component_add_engine(component, description);
    ibus_bus_register_component(bus, component);
  }
  
  ibus_main();

  return 0;
}
