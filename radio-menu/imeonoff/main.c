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
static gboolean process_key_event(IBusEngine *engine,
                                  guint keyval,
                                  guint keycode,
                                  guint modifiers);

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
  engine_class->process_key_event = process_key_event;
}

static IBusPropList *root = NULL;
static IBusProperty *menu = NULL;
static IBusPropList *submenu = NULL;
static IBusProperty *menua = NULL;
static IBusProperty *menub = NULL;
static IBusProperty *menuc = NULL;
static gint g_imeonoff = 0;
static gint g_inputkind = -1;

static void
ibus_sample_engine_init(IBusSampleEngine *engine)
{
  g_debug(G_STRFUNC);
  IBusText *label = ibus_text_new_from_static_string("Radio Menu IME On Off");
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

  label = ibus_text_new_from_static_string("Set IME Off");
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

  label = ibus_text_new_from_static_string("Hiragana");
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

  label = ibus_text_new_from_static_string("Katakana");
  menuc = ibus_property_new("MENUC",
                            PROP_TYPE_RADIO,
                            label,
                            NULL,
                            NULL,
                            TRUE,
                            TRUE,
                            PROP_STATE_UNCHECKED,
                            NULL);
  g_object_ref_sink(menuc);
  ibus_prop_list_append(submenu, menuc);
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
  if (!strcmp(prop_name, "MENUA")) {
    g_debug("%s:%s %s: Disable IME off",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("-");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_CHECKED);
    ibus_property_set_state(menub, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menuc, PROP_STATE_UNCHECKED);
    ibus_engine_update_property(engine, menua);
    g_imeonoff = 0;
  } else if (!strcmp(prop_name, "MENUB")) {
    g_debug("%s:%s %s: set Hiragana",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("あ");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menub, PROP_STATE_CHECKED);
    ibus_property_set_state(menuc, PROP_STATE_UNCHECKED);
    ibus_engine_update_property(engine, menub);
    g_imeonoff = 1;
    g_inputkind = 0;
  } else if (!strcmp(prop_name, "MENUC")) {
    g_debug("%s:%s %s: set Katakana",
            G_STRLOC, G_STRFUNC, prop_name);
    symbol = ibus_text_new_from_static_string("ア");
    ibus_property_set_symbol(menu, symbol);
    ibus_engine_update_property(engine, menu);
    ibus_property_set_state(menua, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menub, PROP_STATE_UNCHECKED);
    ibus_property_set_state(menuc, PROP_STATE_CHECKED);
    ibus_engine_update_property(engine, menuc);
    g_imeonoff = 1;
    g_inputkind = 1;
  }
}

static gboolean is_kanji(guint keyval, guint modifiers)
{
  if (keyval == IBUS_KEY_Zenkaku_Hankaku ||
      ((modifiers & IBUS_MOD4_MASK) && keyval == IBUS_KEY_grave)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

static gboolean process_key_event(IBusEngine *engine,
                                  guint keyval,
                                  guint keycode,
                                  guint modifiers)
{
  const gchar *name = ibus_key_event_to_string(keyval, modifiers);
  g_debug("%s:%s %s keyval: %u(0x%02x), keycode: %u(0x%02x), modifiers: %u(0x%08x)",
          G_STRLOC, G_STRFUNC, name,
          keyval, keyval, keycode, keycode, modifiers, modifiers);

  if (modifiers & IBUS_RELEASE_MASK) {
    g_debug("%s:%s skip to handle release key", G_STRLOC, G_STRFUNC);
    return FALSE;
  }

  g_debug("%s:%s ime on/off: %d input kind: %d",
          G_STRLOC, G_STRFUNC, g_imeonoff, g_inputkind);

  IBusText *symbol;
  if (is_kanji(keyval, modifiers)) {
    if (g_imeonoff) {
      g_debug("%s:%s set IME to off", G_STRLOC, G_STRFUNC);
      g_imeonoff = 0;
      symbol = ibus_text_new_from_static_string("-");
      ibus_property_set_symbol(menu, symbol);
      ibus_engine_update_property(engine, menu);
      ibus_property_set_state(menua, PROP_STATE_CHECKED);
      ibus_engine_update_property(engine, menua);
    } else {
      switch (g_inputkind) {
      case 1:
        g_debug("%s:%s set default to Katakana", G_STRLOC, G_STRFUNC);
        symbol = ibus_text_new_from_static_string("ア");
        ibus_property_set_symbol(menu, symbol);
        ibus_engine_update_property(engine, menu);
        ibus_property_set_state(menuc, PROP_STATE_CHECKED);
        ibus_engine_update_property(engine, menuc);
        break;
      case 0:
      default:
        // set default to Hiragana
        g_debug("%s:%s set default to Hiragana", G_STRLOC, G_STRFUNC);
        symbol = ibus_text_new_from_static_string("あ");
        ibus_property_set_symbol(menu, symbol);
        ibus_engine_update_property(engine, menu);
        ibus_property_set_state(menub, PROP_STATE_CHECKED);
        ibus_engine_update_property(engine, menub);
        break;
      }
      g_imeonoff = 1;
    }
  }
  return FALSE;
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
  GOptionContext *context = g_option_context_new("- IBus RadioMenuIMEOnOff engine");
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
  ibus_factory_add_engine(factory, "radiomenuimeonoff", IBUS_TYPE_SAMPLE_ENGINE);

  if (execute_by_ibus) {
    ibus_bus_request_name(bus, "com.example.IBus.RADIOMENUIMEONOFF", 0);
  } else {
    IBusComponent *component = ibus_component_new("com.example.IBus.RADIOMENUIMEONOFF",
                                                  "Radio Menu IME On Off",
                                                  "1.0",
                                                  "MIT",
                                                  "Kentaro Hayashi",
                                                  "https://github.com/kenhys/ibus-examples",
                                                  "",
                                                  "ibus-engine-radiomenuimeonoff");
    IBusEngineDesc *description = ibus_engine_desc_new("radiomenuimeonoff",
                                                       "RadioMenuIMEOnOff",
                                                       "Radio Menu IME On Off (Japanese Input Method)",
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
