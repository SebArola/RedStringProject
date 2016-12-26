#include "minunit.h"
#include "../Src/Indexation/pileDescripteur.h"

static t_PileDescripteur pile;

void test_setup(){
    init_pile(&pile);
}

void test_teardown() {
}

MU_TEST(test_check){
    mu_check(pile_est_vide(pile));
}
