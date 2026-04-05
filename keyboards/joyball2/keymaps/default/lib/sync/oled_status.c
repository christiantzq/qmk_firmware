#include QMK_KEYBOARD_H
#include "transactions.h"
#include "oled_status.h"
#include "./lib/display/oled.h"

typedef struct _master_to_slave_t {
    bool m2s_flag;
} master_to_slave_t;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    oled_isActive = m2s->m2s_flag;
}

void syncOledStateWithSlave(void) {
  if (is_keyboard_master()) {
    // Interact with slave every 500ms
    static uint32_t last_sync = 0;
    if (timer_elapsed32(last_sync) > 500) {
      // Create an instance of the master_to_slave_t struct
      master_to_slave_t m2s;
      // Set the boolean flag you want to send (e.g., true or false)
      m2s.m2s_flag = oled_isActive; // Or false, depending on your logic
      
      // Use transaction_rpc_send for one-way data transfer
      if(transaction_rpc_exec(USER_SYNC_A, sizeof(m2s), &m2s, 0, NULL)) {
        last_sync = timer_read32();
        //dprint("Master sent flag to slave.\n");
      } else {
        //dprint("Master failed to send flag to slave!\n");
      }
    }
  }
}