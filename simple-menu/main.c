#include <ibus.h>
#include "engine.h"

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
