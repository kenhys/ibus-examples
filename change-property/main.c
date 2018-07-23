#include <ibus.h>
#include <glib.h>

typedef struct _IBusChangePropEngine IBusChangePropEngine;
typedef struct _IBusChangePropEngineClass IBusChangePropEngineClass;

struct _IBusChangePropEngine {
  IBusEngine parent;
};

struct _IBusChangePropEngineClass {
  IBusEngineClass parent;
};

static void ibus_changeprop_engine_class_init(IBusChangePropEngineClass	*klass);
static void ibus_changeprop_engine_init(IBusChangePropEngine *engine);
static void ibus_changeprop_engine_destroy(IBusChangePropEngine *engine);

static void focus_in(IBusEngine *engine);
static void focus_out(IBusEngine *engine);
static void reset(IBusEngine *engine);
static void enable(IBusEngine *engine);
static void disable(IBusEngine *engine);
static gboolean process_key_event(IBusEngine *engine,
                                  guint keyval,
                                  guint keycode,
                                  guint modifiers);

G_DEFINE_TYPE(IBusChangePropEngine, ibus_changeprop_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_CHANGEPROP_ENGINE (ibus_changeprop_engine_get_type())

GType ibus_changeprop_engine_get_type(void);

static void
ibus_changeprop_engine_class_init(IBusChangePropEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_changeprop_engine_destroy;

  engine_class->process_key_event = process_key_event;
  engine_class->enable = enable;
  engine_class->disable = disable;
  engine_class->focus_in = focus_in;
  engine_class->focus_out = focus_out;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;

static void
ibus_changeprop_engine_init(IBusChangePropEngine *engine)
{
  g_debug(G_STRFUNC);
  IBusText *label = ibus_text_new_from_static_string("Menu A");
  root = ibus_prop_list_new();
  g_object_ref_sink(root);;
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

  label = ibus_text_new_from_static_string("SubMenu A");
  IBusProperty *prop = ibus_property_new("SubMenu A KEY",
                                         PROP_TYPE_MENU,
                                         label,
                                         NULL,
                                         NULL,
                                         TRUE,
                                         TRUE,
                                         PROP_STATE_UNCHECKED,
                                         NULL);
  ibus_prop_list_append(submenu, prop);

}

static void
ibus_changeprop_engine_destroy(IBusChangePropEngine *engine)
{
  g_debug(G_STRFUNC);
  if (menu) {
    g_object_unref(menu);
    menu = NULL;
  }
  if (root) {
    g_object_unref(root);
    root = NULL;
  }
  ((IBusObjectClass *)ibus_changeprop_engine_parent_class)->destroy((IBusObject *)engine);
}

static gboolean
process_key_event(IBusEngine *engine,
                  guint       keyval,
                  guint       keycode,
                  guint       modifiers)
{
  g_debug(G_STRFUNC);
  return FALSE;
}

static void
enable(IBusEngine *engine)
{
  g_debug(G_STRFUNC);
}

static void
disable(IBusEngine *engine)
{
  g_debug(G_STRFUNC);
}

static void
focus_in(IBusEngine *engine)
{
  g_debug(G_STRFUNC);

  // It should not be called in engine_init.
  ibus_engine_register_properties((IBusEngine*)engine, root);

  ibus_engine_register_properties((IBusEngine*)engine, root);
}

static void
focus_out(IBusEngine *engine)
{
  g_debug(G_STRFUNC);
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
  GOptionContext *context = g_option_context_new("- IBus ChangeProp engine");
  g_option_context_add_main_entries(context, options, "change-property");

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
  ibus_factory_add_engine(factory, "changeprop", IBUS_TYPE_CHANGEPROP_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.CHANGEPROP", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.CHANGEPROP",
                                                  "Change Property",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-changeprop");
    IBusEngineDesc *description = ibus_engine_desc_new("changeprop",
                                                       "ChangeProp",
                                                       "Change Property (Japanese Input Method)",
                                                       "ja",
                                                       "MIT",
                                                       "Kentaro Hayashi",
                                                       "",
                                                       "default");
    ibus_component_add_engine(component, description);
    ibus_bus_register_component(bus, component);
    g_object_unref(component);
  }
  
  ibus_main();

  return 0;
}
