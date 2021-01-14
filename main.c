#include "ft_printf.h"
#include <stdio.h>

int main()
{

	int a;
	char *b;
	a = 2;
	b = "abcd";
	printf("     %d\n", ft_printf("%082.u", 4183054859u));
	printf("\n");
	printf("     %d\n", printf("%% *.5i 42 == |%*.5i|", 4, 42));
/*
	int res;
	int ft_res;

	printf("-----------------   test char %%   -----------------\n");
	printf("   printf ----- %-10.5%|\n", 'h');
	ft_printf("ft_printf ----- %-10.5%|\n", 'h');
	printf("   printf ----- %020.5%|\n", 'h');
	ft_printf("ft_printf ----- %020.5%|\n", 'h');
	printf("-----------------   test char %% end   -----------------\n\n\n");

	printf("-----------------   test char start   -----------------\n");
	res = printf("   printf ----- %04.5c|\n", 'h');
	ft_res = ft_printf("ft_printf ----- %04.5c|\n", 'h');
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test char end   -----------------\n\n\n");

	printf("-----------------   test string start   -----------------\n");
	printf("   printf ----- %0*s\n", 25, "hello world!");
	ft_printf("ft_printf ----- %0*s\n", 25, "hello world!");
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %-10.3s|\n", "hello world!");
	ft_res = ft_printf("ft_printf ----- %-10.3s|\n", "hello world!");
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %010.3s\n", "hello world!");
	ft_res = ft_printf("ft_printf ----- %010.3s\n", "hello world!");
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %20.s\n", "hello world!");
	ft_res = ft_printf("ft_printf ----- %20.s\n", "hello world!");
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%20.s|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%20.s|\n", 0);
	printf("-----------------   test string end   -----------------\n\n\n");

	printf("-----------------   test pointer start   -----------------\n");
	char *s = malloc(1);
	res = printf("   printf ----- %p\n", NULL);
	ft_res = ft_printf("ft_printf ----- %p\n", NULL);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %p\n", &s);
	ft_res = ft_printf("ft_printf ----- %p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %20p\n", &s);
	ft_res = ft_printf("ft_printf ----- %20p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %020p\n", &s);
	ft_res = ft_printf("ft_printf ----- %020p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %020p\n", NULL);
	ft_res = ft_printf("ft_printf ----- %020p\n", NULL);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %35.55p\n", &s);
	ft_res = ft_printf("ft_printf ----- %35.55p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %035.15p\n", &s);
	ft_res = ft_printf("ft_printf ----- %035.15p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %35.5p\n", &s);
	ft_res = ft_printf("ft_printf ----- %35.5p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %0*.15p\n", 40, &s);
	ft_res = ft_printf("ft_printf ----- %0*.15p\n", 40, &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %05p\n", NULL);
	ft_res = ft_printf("ft_printf ----- %05p\n", NULL);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %5p\n", NULL);
	ft_res = ft_printf("ft_printf ----- %5p\n", NULL);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %70p\n", &s);
	ft_res = ft_printf("ft_printf ----- %70p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-70p|\n", &s);
	ft_res = ft_printf("ft_printf ----- |%-70p|\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test pointer end   -----------------\n\n\n");

	printf("-----------------   test digit start   -----------------\n");
	printf("********************* test №1 *****************\n");
	res = printf("   printf ----- %7.7d\n", -12345);
	ft_res = ft_printf("ft_printf ----- %7.7d\n", -12345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №2 *****************\n");
	res = printf("   printf ----- %-7.7d\n", -12345);
	ft_res = ft_printf("ft_printf ----- %7.7d\n", -12345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №3 *****************\n");
	res = printf("   printf ----- %70d\n", 142);
	ft_res = ft_printf("ft_printf ----- %70d\n", 142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №4 *****************\n");
	res = printf("   printf ----- %.4d\n", 142);
	ft_res = ft_printf("ft_printf ----- %.4d\n", 142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №5 *****************\n");
	res = printf("   printf ----- %5.4d\n", 142);
	ft_res = ft_printf("ft_printf ----- %5.4d\n", 142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №6 *****************\n");
	res = printf("   printf ----- |%15.4d|\n", 142);
	ft_res = ft_printf("ft_printf ----- |%15.4d|\n", 142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №7 *****************\n");
	res = printf("   printf ----- |%-15.4d|\n", 142);
	ft_res = ft_printf("ft_printf ----- |%-15.4d|\n", 142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №8 *****************\n");
	res = printf("   printf ----- |%-15.25d|\n", -142);
	ft_res = ft_printf("ft_printf ----- |%-15.25d|\n", -142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №9 *****************\n");
	res = printf("   printf ----- |%-15d|\n", -33333);
	ft_res = ft_printf("ft_printf ----- |%-15d|\n", -33333);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №10 *****************\n");
	res = printf("   printf ----- |%15d|\n", -22222222);
	ft_res = ft_printf("ft_printf ----- |%15d|\n", -22222222);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №11 *****************\n");
	res = printf("   printf ----- |%-.25d|\n", -8765);
	ft_res = ft_printf("ft_printf ----- |%-.25d|\n", -8765);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №12 *****************\n");
	res = printf("   printf ----- |%-35.25d|\n", -142);
	ft_res = ft_printf("ft_printf ----- |%-35.25d|\n", -142);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №13 *****************\n");
	res = printf("   printf ----- |%.6d|\n", -6);
	ft_res = ft_printf("ft_printf ----- |%.6d|\n", -6);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%07d|\n", -54);
	ft_res = ft_printf("ft_printf ----- |%07d|\n", -54);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №14 *****************\n");
	res = printf("   printf ----- |%07d|\n", 54);
	ft_res = ft_printf("ft_printf ----- |%07d|\n", 54);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №1 *****************\n");
	res = printf("   printf ----- |%03d|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%03d|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №15 *****************\n");
	res = printf("   printf ----- |%10.5d|\n", -216);
	ft_res = ft_printf("ft_printf ----- |%10.5d|\n", -216);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №16 *****************\n");
	res = printf("   printf ----- |%8.5d|\n", 34);
	ft_res = ft_printf("ft_printf ----- |%8.5d|\n", 34);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №17 *****************\n");
	res = printf("   printf ----- |%8.3d|\n", -8434);
	ft_res = ft_printf("ft_printf ----- |%8.3d|\n", -8434);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №18 *****************\n");
	res = printf("   printf ----- |%-8.5d|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%-8.5d|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("********************* test №19 *****************\n");
	res = printf("   printf ----- |%-8.3d|\n", 1230);
	ft_res = ft_printf("ft_printf ----- |%-8.3d|\n", 1230);
	printf("********************* test №20 *****************\n");
	res = printf("   printf ----- |%8.d|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%8.d|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test digit end   -----------------\n\n\n");

	printf("-----------------   test unsigned start   -----------------\n");
	res = printf("   printf ----- |%u|\n", -2);
	ft_res = ft_printf("ft_printf ----- |%u|\n", -2);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%30u|\n", -12342);
	ft_res = ft_printf("ft_printf ----- |%30u|\n", -12342);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-30u|\n", 12342);
	ft_res = ft_printf("ft_printf ----- |%-30u|\n", 12342);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-30.25u|\n", 12342);
	ft_res = ft_printf("ft_printf ----- |%-30.25u|\n", 12342);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-30.45u|\n", 12342);
	ft_res = ft_printf("ft_printf ----- |%-30.45u|\n", 12342);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-30.0u|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%-30.0u|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test unsigned end   -----------------\n\n\n");

	printf("-----------------   test i start   -----------------\n");
	res = printf("   printf ----- |%i|\n", -1);
	ft_res = ft_printf("ft_printf ----- |%i|\n", -1);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%i|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%i|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%i|\n", 213456712345);
	ft_res = ft_printf("ft_printf ----- |%i|\n", 213456712345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%i|\n", -213456712345);
	ft_res = ft_printf("ft_printf ----- |%i|\n", -213456712345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%023.4i|\n", -213456712345);
	ft_res = ft_printf("ft_printf ----- |%023.4i|\n", -213456712345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-030.20i|\n", -345);
	ft_res = ft_printf("ft_printf ----- |%-030.20i|\n", -345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	printf("-----------------   test i end   -----------------\n\n\n");

	printf("-----------------   test x start   -----------------\n");
	res = printf("   printf ----- |%x|\n", -1);
	ft_res = ft_printf("ft_printf ----- |%x|\n", -1);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%x|\n", 21345);
	ft_res = ft_printf("ft_printf ----- |%x|\n", 21345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%10.3x|\n", 123456);
	ft_res = ft_printf("ft_printf ----- |%10.3x|\n", 123456);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%20.5x|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%20.5x|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5.20x|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%5.20x|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-020.5x|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%-020.5x|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020.5x|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020.5x|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020.x|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020.x|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020x|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020x|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%05x|\n", 34);
	ft_res = ft_printf("ft_printf ----- |%05x|\n", 34);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%7x|\n", 12345621345);
	ft_res = ft_printf("ft_printf ----- |%7x|\n", 12345621345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test x end   -----------------\n\n\n");

	printf("-----------------   test X start   -----------------\n");
	res = printf("   printf ----- |%X|\n", -1);
	ft_res = ft_printf("ft_printf ----- |%X|\n", -1);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%X|\n", 21345);
	ft_res = ft_printf("ft_printf ----- |%X|\n", 21345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%10.3X|\n", 123456);
	ft_res = ft_printf("ft_printf ----- |%10.3X|\n", 123456);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%20.5X|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%20.5X|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5.20X|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%5.20X|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-020.5X|\n", 3);
	ft_res = ft_printf("ft_printf ----- |%-020.5X|\n", 3);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020.5X|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020.5X|\n", 0);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020.X|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020.X|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%020X|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%020X|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%05X|\n", 34);
	ft_res = ft_printf("ft_printf ----- |%05X|\n", 34);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%7X|\n", 12345621345);
	ft_res = ft_printf("ft_printf ----- |%7X|\n", 12345621345);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("-----------------   test X end   -----------------\n\n\n");

	printf("**************************************************\n");
	res = printf("   printf ----- |%20.5x|\n", 33333);
	ft_res = ft_printf("ft_printf ----- |%20.5x|\n", 33333);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5.20x|\n", 33333);
	ft_res = ft_printf("ft_printf ----- |%5.20x|\n", 33333);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-020.5x|\n", 33333);
	ft_res = ft_printf("ft_printf ----- |%-020.5x|\n", 33333);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%-8.5x|\n", 34);
	ft_res = ft_printf("ft_printf ----- |%-8.5x|\n", 34);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%2.9p|\n", 1234);
	ft_res = ft_printf("ft_printf ----- |%2.9p|\n", 1234);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%20.16p|\n", 1234);
	ft_res = ft_printf("ft_printf ----- |%20.16p|\n", 1234);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%15.20p|\n", 1234);
	ft_res = ft_printf("ft_printf ----- |%15.20p|\n", 1234);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5.7p|\n", 1);
	ft_res = ft_printf("ft_printf ----- |%5.7p|\n", 1);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%.5p|\n", 0);
	ft_res = ft_printf("ft_printf ----- |%.5p|\n", 0);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- %020p\n", &s);
	ft_res = ft_printf("ft_printf ----- %020p\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5|\n");
	ft_res = ft_printf("ft_printf ----- |%5|\n");
	printf("res = %d          ft_res = %d\n", res, ft_res);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5.0| |%s|\n", &s);
	ft_res = ft_printf("ft_printf ----- |%5.0| |%s|\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res, "q2er", "123 4324refwa", 123234);
	printf("**************************************************\n");
	res = printf("   printf ----- |%5| |%s|\n", &s);
	ft_res = ft_printf("ft_printf ----- |%5| |%s|\n", &s);
	printf("res = %d          ft_res = %d\n", res, ft_res, "q2er", "123 4324refwa", 123234);
	res = printf("   printf ----- %", &s);
	ft_res = ft_printf("ft_printf ----- %", &s);
	printf("\nres = %d          ft_res = %d\n", res, ft_res);
	printf("---------------------------------------------------------\n", &s);
	ft_printf("%%%%%%%%d\n", 42);
	printf("%%%%%%%%d\n", 42);*/
	return 0;
}