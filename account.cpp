#include "account.hpp"

Account global("James Joyce");

int main() {
    Account local("Anna Livia Plurabelle", 10000);
    Account &loc_ref = global;
    Account *pact = 0;

    {
        Account local_too("Stephen Hero");
        pact = new Account("Stephen Dedalus");
    }

    delete pact;

    return 0;
}
