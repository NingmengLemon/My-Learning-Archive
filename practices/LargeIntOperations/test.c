#include "bnum.h"

void test(void){
    bnum n = new_bnum();
    bnum m = new_bnum();
    bnum r = new_bnum();
    uint64_t tmp = 0;

    input_from_ui64(n,18446744073709551610ull);
    printf("Test input number (ui64)\n");
    print_bnum(n);

    input_from_str(n,"18446744073709551610000");
    printf("\nTest input number (str)\n");
    print_bnum(n);

    printf("\nTest add number\n");
    input_from_ui64(m,18446744073709551615ull);
    add_bnum(m,n,r);
    print_bnum(r);

    printf("\nTest sub number\n");
    input_from_ui64(n,1919810114514191999ull);
    subtract_bnum(m,n,r);
    print_bnum(r);

    printf("\nTest multiply number\n");
    multiply_bnum(m, n, r);
    print_bnum(r);

    printf("\nTest module number\n");
    module_bnum(m,n,r);
    print_bnum(r);

    printf("\nTest convert number\n");
    tmp = bnum_to_ui64(r);
    printf("%llu",tmp);

    printf("\nTest multimod number\n");
    del_bnum(r);
    del_bnum(m);
    del_bnum(n);
    printf("%llu\n",multimod_ok(
        12547581493777951506ull,
        7840200090082797186ull,
        4718536181305754417ull)
        // ==1006762042485963158ull
        );
    printf("%llu\n",multimod_ok(
        9114078677679929330ull,
        10011217312207496972ull,
        4224850533405452362ull)
        // ==1015941353099777946ull
        );
    printf("%llu\n",multimod_ok(
        6573265899388197304ull,
        9487499146431324957ull,
        608107446957448437ull)
        // ==157170530191189206ull
        );
    printf("%llu\n",multimod_ok(
        7117836755559922609ull,
        7289845773136167824ull,
        5358375867059079814ull)
        // ==2833009027640776056ull
        );
    printf("%llu\n",multimod_ok(
        3971928421627408404ull,
        5322745319699324877ull,
        1373401571166321901ull)
        // ==75633027866585136ull
        );
    printf("%llu\n",multimod_ok(
        434693231937754679ull,
        282372467057234242ull,
        13136775774323946633ull)
        // ==7695857118303317183ull
        );
    printf("%llu\n",multimod_ok(
        3312228923687098908ull,
        14729079364782058227ull,
        5655843353141937643ull)
        // ==1279900054323543687ull
        );
    printf("%llu\n",multimod_ok(
        935129609174317231ull,
        10935600981467441067ull,
        16921101872659373993ull)
        // ==13530510238416508164ull
        );
    printf("%llu\n",multimod_ok(
        14122009052383619366ull,
        9941563575036325569ull,
        3405880916245858374ull)
        // ==1688948043588152232ull
        );
}

int main(void){
    test();
    return EXIT_SUCCESS;
}