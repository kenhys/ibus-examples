#include <ibus.h>
#include <glib.h>

typedef struct _IBusChangeInputModeIconEngine IBusChangeInputModeIconEngine;
typedef struct _IBusChangeInputModeIconEngineClass IBusChangeInputModeIconEngineClass;

struct _IBusChangeInputModeIconEngine {
  IBusEngine parent;
};

struct _IBusChangeInputModeIconEngineClass {
  IBusEngineClass parent;
};

static void ibus_changeinputmodeicon_engine_class_init(IBusChangeInputModeIconEngineClass	*klass);
static void ibus_changeinputmodeicon_engine_init(IBusChangeInputModeIconEngine *engine);
static void ibus_changeinputmodeicon_engine_destroy(IBusChangeInputModeIconEngine *engine);

static void focus_in(IBusEngine *engine);
static void focus_out(IBusEngine *engine);
static void reset(IBusEngine *engine);
static void enable(IBusEngine *engine);
static void disable(IBusEngine *engine);
static void property_activate(IBusEngine *engine,
                              const gchar *prop_name,
                              guint prop_state);

G_DEFINE_TYPE(IBusChangeInputModeIconEngine, ibus_changeinputmodeicon_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_CHANGEINPUTMODEICON_ENGINE (ibus_changeinputmodeicon_engine_get_type())

GType ibus_changeinputmodeicon_engine_get_type(void);

static void
ibus_changeinputmodeicon_engine_class_init(IBusChangeInputModeIconEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_changeinputmodeicon_engine_destroy;

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
ibus_changeinputmodeicon_engine_init(IBusChangeInputModeIconEngine *engine)
{
  g_debug(G_STRFUNC);
  IBusText *label = ibus_text_new_from_static_string("Change Icon");
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

  label = ibus_text_new_from_static_string("Set Icon A");
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

  label = ibus_text_new_from_static_string("Set Icon B");
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

}

static void
ibus_changeinputmodeicon_engine_destroy(IBusChangeInputModeIconEngine *engine)
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
  ((IBusObjectClass *)ibus_changeinputmodeicon_engine_parent_class)->destroy((IBusObject *)engine);
}

static void
property_activate(IBusEngine *engine,
                  const gchar *prop_name,
                  guint prop_state)
{
  g_debug(G_STRFUNC);

  if (!strcmp(prop_name, "MENUA")) {
    g_debug("%s:%s set icon to InputMode menu: %s", G_STRLOC, G_STRFUNC, SAMPLE_A_ICON);
    ibus_property_set_icon(menu, SAMPLE_A_ICON);
  } else if (!strcmp(prop_name, "MENUB")) {
    g_debug("%s:%s set icon to InputMode menu: %s", G_STRLOC, G_STRFUNC, SAMPLE_B_ICON);
    ibus_property_set_icon(menu, SAMPLE_B_ICON);
  }
  ibus_engine_update_property(engine, menu);
}

static void
enable(IBusEngine *engine)
{
  g_debug(G_STRFUNC);

  // It should not be called in engine_init.
  ibus_engine_register_properties((IBusEngine*)engine, root);
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
  GOptionContext *context = g_option_context_new("- IBus ChangeInputModeIcon engine");
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
  ibus_factory_add_engine(factory, "changeinputmodeicon", IBUS_TYPE_CHANGEINPUTMODEICON_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.CHANGEINPUTMODEICON", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.CHANGEINPUTMODEICON",
                                                  "Change Input Mode Icon",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-changeinputmodeicon");
    IBusEngineDesc *description = ibus_engine_desc_new("changeinputmodeicon",
                                                       "ChangeInputModeIcon",
                                                       "Change Input Mode Icon (Japanese Input Method)",
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
