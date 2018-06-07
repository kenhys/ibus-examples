#include "engine.h"

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
