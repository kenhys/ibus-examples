#include <ibus.h>
#include <glib.h>

typedef struct _IBusSampleEngine IBusSampleEngine;
typedef struct _IBusSampleEngineClass IBusSampleEngineClass;

struct _IBusSampleEngine {
  IBusEngine parent;
};

struct _IBusSampleEngineClass {
  IBusEngineClass parent;
};

static void ibus_changeinputmodesymbol_engine_class_init(IBusSampleEngineClass	*klass);
static void ibus_changeinputmodesymbol_engine_init(IBusSampleEngine *engine);
static void ibus_changeinputmodesymbol_engine_destroy(IBusSampleEngine *engine);

static void focus_in(IBusEngine *engine);
static void focus_out(IBusEngine *engine);
static void reset(IBusEngine *engine);
static void enable(IBusEngine *engine);
static void disable(IBusEngine *engine);
static void property_activate(IBusEngine *engine,
                              const gchar *prop_name,
                              guint prop_state);

G_DEFINE_TYPE(IBusSampleEngine, ibus_changeinputmodesymbol_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_CHANGEINPUTMODESYMBOL_ENGINE (ibus_changeinputmodesymbol_engine_get_type())

GType ibus_changeinputmodesymbol_engine_get_type(void);

static void
ibus_changeinputmodesymbol_engine_class_init(IBusSampleEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_changeinputmodesymbol_engine_destroy;

  engine_class->enable = enable;
  engine_class->disable = disable;
  engine_class->focus_in = focus_in;
  engine_class->focus_out = focus_out;
  engine_class->property_activate = property_activate;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;

static void
ibus_changeinputmodesymbol_engine_init(IBusSampleEngine *engine)
{
  g_debug(G_STRFUNC);
  IBusText *label = ibus_text_new_from_static_string("Change Symbol");
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
  label = ibus_text_new_from_static_string("-");
  ibus_property_set_symbol(menu, label);
  g_object_ref_sink(menu);
  ibus_prop_list_append(root, menu);

  label = ibus_text_new_from_static_string("Set Symbol A");
  IBusProperty *prop = ibus_property_new("MENUA",
                                         PROP_TYPE_NORMAL,
                                         label,
                                         NULL,
                                         NULL,
                                         TRUE,
                                         TRUE,
                                         PROP_STATE_UNCHECKED,
                                         NULL);
  g_object_ref_sink(prop);
  ibus_prop_list_append(submenu, prop);

  label = ibus_text_new_from_static_string("Set Symbol B");
  prop = ibus_property_new("MENUB",
                           PROP_TYPE_NORMAL,
                           label,
                           NULL,
                           NULL,
                           TRUE,
                           TRUE,
                           PROP_STATE_UNCHECKED,
                           NULL);
  g_object_ref_sink(prop);
  ibus_prop_list_append(submenu, prop);

  label = ibus_text_new_from_static_string("Dummy Tool");
  prop = ibus_property_new("TOOL",
                           PROP_TYPE_MENU,
                           label,
                           NULL,
                           NULL,
                           TRUE,
                           TRUE,
                           PROP_STATE_UNCHECKED,
                           NULL);
  g_object_ref_sink(prop);
  ibus_prop_list_append(root, prop);
}

static void
ibus_changeinputmodesymbol_engine_destroy(IBusSampleEngine *engine)
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
  ((IBusObjectClass *)ibus_changeinputmodesymbol_engine_parent_class)->destroy((IBusObject *)engine);
}

static void
property_activate(IBusEngine *engine,
                  const gchar *prop_name,
                  guint prop_state)
{
  g_debug(G_STRFUNC);

  g_debug("%s:%s: prop_name: %s prop_state: 0x%08x",
          G_STRLOC, G_STRFUNC, prop_name, prop_state);

  IBusText *symbol;
  if (!strcmp(prop_name, "MENUA")) {
    g_debug("%s:%s %s: set symbol(A) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("A");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
  } else if (!strcmp(prop_name, "MENUB")) {
    g_debug("%s:%s %s: set symbol(B) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("B");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
  }
}

static void
enable(IBusEngine *engine)
{
  g_debug(G_STRFUNC);

  if (menu) {
    IBusText *symbol;
    symbol = ibus_text_new_from_static_string("-");
    ibus_property_set_symbol(menu, symbol);
  }

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
  GOptionContext *context = g_option_context_new("- IBus Sample engine");
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
  ibus_factory_add_engine(factory, "changeinputmodesymbol", IBUS_TYPE_CHANGEINPUTMODESYMBOL_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.CHANGEINPUTMODESYMBOL", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.CHANGEINPUTMODESYMBOL",
                                                  "Change Input Mode Symbol",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-changeinputmodesymbol");
    IBusEngineDesc *description = ibus_engine_desc_new("changeinputmodesymbol",
                                                       "ChangeInputModeSymbol",
                                                       "Change Input Mode Symbol (Japanese Input Method)",
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
