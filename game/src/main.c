#include "loader/loader.h"
#include "mgbalog.h"
#include "serial/C_LinkCard.h"
#include "tonc_bios.h"
#include <tonc.h>

#include "serial/C_LinkCard.h"

C_LinkCardHandle linkCard;

bool checkForCancel() { return 0; }

void sendPayload() {
  mgbalog(DEBUG, "sendPayload start");

  C_LinkCard_ConnectedDevice device =
      C_LinkCard_getConnectedDevice(linkCard, checkForCancel);

  if (device == C_LINK_CARD_CONNECTED_DEVICE_E_READER_USA) {
    mgbalog(DEBUG, "US ereader connected");
  } else if (device == C_LINK_CARD_CONNECTED_DEVICE_E_READER_JAP) {
    mgbalog(DEBUG, "JPN ereader connected");
  } else {
    mgbalog(DEBUG, "unknown or no device: %i", device);
  }

  C_LinkCard_SendResult result =
      C_LinkCard_sendLoader(linkCard, loader, LOADER_COUNT, checkForCancel);

  if (result == C_LINK_CARD_SEND_RESULT_SUCCESS) {
    mgbalog(DEBUG, "sendPayload: success");
  } else {
    mgbalog(DEBUG, "sendPayload: failure: %i", result);
  }
}

void isr_main() {}

int main() {
  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  mgbalog(DEBUG, "game started");
  linkCard = C_LinkCard_createDefault();

  while (1) {
    VBlankIntrWait();
    key_poll();

    if (key_hit(KEY_A)) {
      sendPayload();
    }
  }
  return 0;
}