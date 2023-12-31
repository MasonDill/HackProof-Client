#ifndef HACKPROOF_LEDGER
#define HACKPROOF_LEDGER
#include <stdint.h>
// Define HackProof Constants
#define EPOCH_CONSTANT 0XFFFFFFFF
#define TERMINATOR_CONSTANT 0XFFFFFFFE
#define PUBLIC_KEY_BIT_LENGTH 256
#define LEDGER_BUFFER_SIZE 10
#define LEDGER_SAVE_LOCATION "/home/mason/Documents/NetHack/ledgers/ledger.txt"

struct LedgerEntry{
    int player_action;
    int combined_gamestate_id;
    int current_gamestate_id;
    int message;
    int signature;
};

struct HackProofLedger{
    int FINAL_SCORE;
    uint8_t Pk[PUBLIC_KEY_BIT_LENGTH];
    struct LedgerEntry entries[LEDGER_BUFFER_SIZE];
    int ledger_length;
};

// Helper functions
int extract_combined_gamestate_id(int message, int player_action);
int extract_new_gamestate_id(int combined_gamestate_id, int old_gamestate_id);
struct LedgerEntry create_ledger_entry(int player_action, int combined_gamestate_id, int current_gamestate_id, int message, int signature);
// Public functions
void write_ledger_header(int initial_gamestate_seed, uint8_t public_key[256]);
void add_ledger_line(struct HackProofLedger, struct LedgerEntry);
struct HackProofLedger read_ledger_file(char* file_name);
// Private functions
void write_ledger_line(struct LedgerEntry a_entry);

#endif // HACKPROOF_LEDGER