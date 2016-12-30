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


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_check);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}
