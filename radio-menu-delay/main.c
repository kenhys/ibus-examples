#include <ibus.h>
#include <glib.h>

typedef struct _IBusRadioMenuDelayEngine IBusRadioMenuDelayEngine;
typedef struct _IBusRadioMenuDelayEngineClass IBusRadioMenuDelayEngineClass;

struct _IBusRadioMenuDelayEngine {
  IBusEngine parent;
};

struct _IBusRadioMenuDelayEngineClass {
  IBusEngineClass parent;
};

static void ibus_radiomenudelay_engine_class_init(IBusRadioMenuDelayEngineClass	*klass);
static void ibus_radiomenudelay_engine_init(IBusRadioMenuDelayEngine *engine);
static void ibus_radiomenudelay_engine_destroy(IBusRadioMenuDelayEngine *engine);

static void focus_in(IBusEngine *engine);
static void focus_out(IBusEngine *engine);
static void reset(IBusEngine *engine);
static void enable(IBusEngine *engine);
static void disable(IBusEngine *engine);
static void property_activate(IBusEngine *engine,
                              const gchar *prop_name,
                              guint prop_state);

G_DEFINE_TYPE(IBusRadioMenuDelayEngine, ibus_radiomenudelay_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_RADIOMENUDELAY_ENGINE (ibus_radiomenudelay_engine_get_type())

GType ibus_radiomenudelay_engine_get_type(void);

static void
ibus_radiomenudelay_engine_class_init(IBusRadioMenuDelayEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_radiomenudelay_engine_destroy;

  engine_class->enable = enable;
  engine_class->disable = disable;
  engine_class->focus_in = focus_in;
  engine_class->focus_out = focus_out;
  engine_class->property_activate = property_activate;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;
static IBusProperty *menua = NULL;
static IBusProperty *menub = NULL;

static void
ibus_radiomenudelay_engine_init(IBusRadioMenuDelayEngine *engine)
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
  menua = ibus_property_new("MENUA",
                            PROP_TYPE_RADIO,
                            label,
                            NULL,
                            NULL,
                            TRUE,
                            TRUE,
                            PROP_STATE_UNCHECKED,
                            NULL);
  g_object_ref_sink(menua);
  ibus_prop_list_append(submenu, menua);

  label = ibus_text_new_from_static_string("Set Symbol B");
  menub = ibus_property_new("MENUB",
                            PROP_TYPE_RADIO,
                            label,
                            NULL,
                            NULL,
                            TRUE,
                            TRUE,
                            PROP_STATE_UNCHECKED,
                            NULL);
  g_object_ref_sink(menub);
  ibus_prop_list_append(submenu, menub);

  label = ibus_text_new_from_static_string("Dummy Tool");
  IBusProperty *prop = ibus_property_new("TOOL",
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
ibus_radiomenudelay_engine_destroy(IBusRadioMenuDelayEngine *engine)
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
  if (menua) {
    g_object_unref(menua);
    root = NULL;
  }
  if (menub) {
    g_object_unref(menub);
    root = NULL;
  }
  ((IBusObjectClass *)ibus_radiomenudelay_engine_parent_class)->destroy((IBusObject *)engine);
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
    /* there is a 1 step delay to be changed. */
    ibus_property_set_state(menua, PROP_STATE_CHECKED);
    ibus_property_set_state(menub, PROP_STATE_UNCHECKED);
    ibus_engine_update_property(engine, menu);
  } else if (!strcmp(prop_name, "MENUB")) {
    g_debug("%s:%s %s: set symbol(B) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("B");
    ibus_property_set_symbol(menu, symbol);
    ibus_property_set_state(menua, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menub, PROP_STATE_CHECKED);
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
  GOptionContext *context = g_option_context_new("- IBus RadioMenuDelay engine");
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
  ibus_factory_add_engine(factory, "radiomenudelay", IBUS_TYPE_RADIOMENUDELAY_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.RADIOMENUDELAY", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.RADIOMENU",
                                                  "Radio Menu Delay",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-radiomenudelay");
    IBusEngineDesc *description = ibus_engine_desc_new("radiomenudelay",
                                                       "RadioMenuDelay",
                                                       "Radio Menu Delay (Japanese Input Method)",
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
