#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "RSA.h"

#define MESSAGE_PATH "./generator/inputs.txt"
#define LENGTH_BYTES 16

int main(int argc, char* argv[]) {
	uint64x2_t message;

	//timing
	clock_t encrypt_start, encrypt_end, decrypt_start, decrypt_end, loop_start, loop_end;

	uint8_t line[10];
	FILE* stream = fopen(MESSAGE_PATH, "r");
	FILE* output = fopen("./results/results.csv", "w+");
	fprintf(output, "encrypt,decrypt\n");
	loop_start = clock();
	//int i = 0;
	while (1) {
		encrypt_start = 0;
		encrypt_end = 0;
		decrypt_start = 0;
		decrypt_end = 0;

		if (fgets(line, 11, stream)  == NULL) break;
		//fprintf(stderr, "Line %i: %s\n", i++, line);

		message = copyStr(line);
		//printU128(message, "Message");

		encrypt_start = clock();
		uint64x2_t encrypted = Encypt(message);
		encrypt_end = clock();
		//printU128(encrypted, "Encrypted");


		decrypt_start = clock();
		uint64x2_t decrypted = Decrypt(encrypted);
		decrypt_end = clock();

		double encrypt_time = (double)(encrypt_end - encrypt_start) / CLOCKS_PER_SEC;
		double decrypt_time = (double)(decrypt_end - decrypt_start) / CLOCKS_PER_SEC;
		//printf("encrypt time: %.7f\n", encrypt_time);
		//printf("decrypt time: %.7f\n", decrypt_time);
		fprintf(output, "%.7f,%.7f\n", encrypt_time, decrypt_time);

		//printU128(decrypted, "Decrypted");

		if (!equal(message, decrypted)) {
			printf("NOT euqal!");
			return 1;
		}

	}
	loop_end = clock();
	fclose(stream);
	fclose(output);

	double loop_time = (double)(loop_end - loop_start) / CLOCKS_PER_SEC;
	printf("loop time: %.20f\n", loop_time);
	//fprintf(output, "%.20f", loop_time);

	return 1;
}