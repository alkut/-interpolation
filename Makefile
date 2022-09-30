library:
	gcc -shared -fPIC interpolation.c TestFunctions.c HermitInterpolation.c Common.c CubicSpline.c -lm -o libinter.so
compile:
	gcc main.c -Wl,-rpath='./' -L. -linter -o main
test:
	gcc test.c -Wl,-rpath='./' -L. -linter -o test_inter
run_test:library test
	./test_inter
run_main:library compile
	./main
