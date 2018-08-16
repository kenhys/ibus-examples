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

static void ibus_sample_engine_class_init(IBusSampleEngineClass	*klass);
static void ibus_sample_engine_init(IBusSampleEngine *engine);
static void ibus_sample_engine_destroy(IBusSampleEngine *engine);

static void focus_in(IBusEngine *engine);
static void focus_out(IBusEngine *engine);
static void reset(IBusEngine *engine);
static void enable(IBusEngine *engine);
static void disable(IBusEngine *engine);
static void property_activate(IBusEngine *engine,
                              const gchar *prop_name,
                              guint prop_state);

G_DEFINE_TYPE(IBusSampleEngine, ibus_sample_engine, IBUS_TYPE_ENGINE)

#define IBUS_TYPE_SAMPLE_ENGINE (ibus_sample_engine_get_type())

GType ibus_sample_engine_get_type(void);

static void
ibus_sample_engine_class_init(IBusSampleEngineClass *klass)
{
  g_debug(G_STRFUNC);
  IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (klass);
  IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

  ibus_object_class->destroy = (IBusObjectDestroyFunc)ibus_sample_engine_destroy;

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
static IBusProperty *menuc = NULL;

typedef struct _IBusRadioMenuFromArrayMenuProperty {
    guint id;
    const char *key;
    const char *label;
    const char *parent_key;
} IBusRadioMenuFromArrayMenuProperty;

static IBusRadioMenuFromArrayMenuProperty menus[] = {
  {
    0,
    "InputMode",
    "RadioMenuFromArray Test",
    0
  },
  {
    1,
    "RadioMenuA",
    "Set symbol A",
    "InputMode"
  },
  {
    2,
    "RadioMenuB",
    "Set symbol B",
    "InputMode"
  },
  {
    3,
    "RadioMenuC",
    "Set symbol C",
    "InputMode"
  },
};

static void
ibus_radiomenufromarray_engine_init(IBusRadioMenuFromArrayEngine *engine)
{
  g_debug(G_STRFUNC);
  root = ibus_prop_list_new();
  g_object_ref_sink(root);;

  IBusPropList *parent = NULL;
  IBusProperty *prop = NULL;
    
  for (guint i = 0; i < G_N_ELEMENTS(menus); i++) {
    IBusRadioMenuFromArrayMenuProperty menuitem = menus[i];
    IBusText *label = ibus_text_new_from_static_string(menuitem.label);
    IBusPropType prop_type = PROP_TYPE_NORMAL;
    IBusPropState prop_state = PROP_STATE_UNCHECKED;
    gboolean sensitive = TRUE;
    if (menuitem.id == 0) {
      /* parent menu */
      prop = ibus_property_new(menuitem.key,
                               PROP_TYPE_MENU,
                               label,
                               NULL,
                               NULL,
                               sensitive,
                               TRUE,
                               prop_state,
                               NULL);
      menu = prop;
      g_object_ref_sink(menu);
    } else {
      prop = ibus_property_new(menuitem.key,
                               PROP_TYPE_RADIO,
                               label,
                               NULL,
                               NULL,
                               sensitive,
                               TRUE,
                               prop_state,
                               NULL);
      switch (menuitem.id) {
      case 1:
        menua = prop;
        g_object_ref_sink(menua);
        break;
      case 2:
        menub = prop;
        g_object_ref_sink(menub);
        break;
      case 3:
        menuc = prop;
        g_object_ref_sink(menuc);
        break;
      default:
        break;
      }
    }
    if (!menuitem.parent_key) {
      parent = ibus_prop_list_new();
      ibus_property_set_sub_props(prop, parent);
      ibus_prop_list_append(root, prop);
    } else {
      ibus_prop_list_append(parent, prop);
    }
  }
}

static void
ibus_sample_engine_destroy(IBusSampleEngine *engine)
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
    menua = NULL;
  }
  if (menub) {
    g_object_unref(menub);
    menub = NULL;
  }
  if (menuc) {
    g_object_unref(menuc);
    menuc = NULL;
  }
  ((IBusObjectClass *)ibus_sample_engine_parent_class)->destroy((IBusObject *)engine);
}

static void
property_activate(IBusEngine *engine,
                  const gchar *prop_name,
                  guint prop_state)
{
  g_debug(G_STRFUNC);

  g_debug("%s:%s: prop_name: %s prop_state: 0x%08x",
          G_STRLOC, G_STRFUNC, prop_name, prop_state);

  if (prop_state != PROP_STATE_CHECKED) {
    g_debug("%s:%s: skip to update %s if prop_state(0x%08x) != PROP_STATE_CHECKED",
            G_STRLOC, G_STRFUNC, prop_name, prop_state);
    return;
  }

  IBusText *symbol;
  if (!strcmp(prop_name, "RadioMenuA")) {
    g_debug("%s:%s %s: set symbol(A) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("A");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_CHECKED);
    ibus_property_set_state(menub, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menuc, PROP_STATE_UNCHECKED);
    ibus_engine_update_property(engine, menua);
  } else if (!strcmp(prop_name, "RadioMenuB")) {
    g_debug("%s:%s %s: set symbol(B) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("B");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menub, PROP_STATE_CHECKED);
    ibus_property_set_state(menuc, PROP_STATE_UNCHECKED);
    ibus_engine_update_property(engine, menub);
  } else if (!strcmp(prop_name, "RadioMenuC")) {
    g_debug("%s:%s %s: set symbol(C) to InputMode menu",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("C");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menub, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menuc, PROP_STATE_CHECKED);
    ibus_engine_update_property(engine, menuc);
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
  GOptionContext *context = g_option_context_new("- IBus RadioMenuFromArray engine");
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
  ibus_factory_add_engine(factory, "radiomenufromarray", IBUS_TYPE_SAMPLE_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.RADIOMENUFROMARRAY", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.RADIOMENUFROMARRAY",
                                                  "Radio Menu From Array",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-radiomenufromarray");
    IBusEngineDesc *description = ibus_engine_desc_new("radiomenufromarray",
                                                       "RadioMenuFromArray",
                                                       "Radio Menu From Array (Japanese Input Method)",
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
