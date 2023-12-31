#include <stdio.h>
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

// Private functions
void write_ledger_line(struct LedgerEntry a_entry){
    FILE *file;
    file = fopen(LEDGER_SAVE_LOCATION, "ab");  // Open the file for appending in binary mode

    if (file == NULL) {
        perror("Error opening ledger file");
        return;
    }

    // Write the new entry to the file
    fwrite(&a_entry, sizeof(struct LedgerEntry), 1, file);

    fclose(file);
}


// Public functions
void write_ledger_header(int initial_gamestate_seed, uint8_t public_key[256]) {
    FILE *file;
    file = fopen(LEDGER_SAVE_LOCATION, "wb");  // Open the file for writing in binary mode

    if (file == NULL) {
        perror("Error opening ledger file");
        return;
    }

    fprintf(file, "%x\t", initial_gamestate_seed);

    // Write each element of the array to the file with tab separation
    for (size_t i = 0; i < PUBLIC_KEY_BIT_LENGTH; i++) {
        fprintf(file, "%x", public_key[i]);
    }

    // Close the file
    fclose(file);
}

void add_ledger_line(struct HackProofLedger a_ledger, struct LedgerEntry a_entry){
    a_ledger.entries[a_ledger.ledger_length] = a_entry;
    a_ledger.ledger_length++;

    // Check if the buffer is full or the game is over
    if (a_ledger.ledger_length>=LEDGER_BUFFER_SIZE || a_entry.player_action == TERMINATOR_CONSTANT){
        
        for(int entry = 0; entry < a_ledger.ledger_length; entry++){
            write_ledger_line(a_ledger.entries[entry]);
        }

        // Clear the Buffer
        a_ledger.ledger_length = 0;
    }
}
struct HackProofLedger read_ledger_file(char* file_name){
    return; // TODO: Implement streamreader
}