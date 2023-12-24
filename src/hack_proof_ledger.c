#include <hack_proof_ledger.h>

int extract_combined_gamestate_id(int message, int player_action){
    return message - player_action;
}

int extract_new_gamestate_id(int combined_gamestate_id, int old_gamestate_id){
    return combined_gamestate_id ^ old_gamestate_id;
}

struct LedgerEntry create_ledger_entry(int player_action, int combined_gamestate_id, int current_gamestate_id, int message, int signature){
    struct LedgerEntry new_entry;
    new_entry.player_action = player_action;
    new_entry.combined_gamestate_id = combined_gamestate_id;
    new_entry.current_gamestate_id = current_gamestate_id;
    new_entry.message = message;
    new_entry.signature = signature;
}

// Public functions
void write_ledger_header(int initial_gamestate_seed, int public_key){
    return; //TODO: Implement streamwriter
}

void add_ledger_line(struct HackProofLedger a_ledger, struct LedgerEntry a_entry){
    a_ledger.entries[a_ledger.ledger_length] = a_entry;
    a_ledger.ledger_length++;

    // Check if the buffer is full or the game is over
    if (a_ledger.ledger_length>=LEDGER_BUFFER_SIZE || a_entry.player_action == TERMINATOR_CONSTANT){
        write_ledger_file(a_ledger);
        a_ledger.ledger_length = 0;
    }
}
struct HackProofLedger read_ledger_file(char* file_name){
    return; // TODO: Implement streamreader
}
// Private functions
void write_ledger_ledger(struct HackProofLedger a_ledger){
    for(int i = 0; i < a_ledger.ledger_length ; i++){
        continue; //TODO: Implement streamwriter
    }
    return;
}
