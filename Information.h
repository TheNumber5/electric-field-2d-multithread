//Contains information about the main program.

void ShowInformation() {
	printf("Program that simulates the field of electric potentials from charged particles, using 4 threads.\n\n");
	printf("You can view more help at:\n");
	printf("https://github.com/TheNumber5/electric-potential-2d-multithread\n");
	printf("Version: v1.0\n");
	printf("Date: 09/06/2024");
}

void CreateNewFile() {
	FILE *input = fopen("in.txt", "wb");
	fprintf(input, "20 20 7 7\n0 1 0.000000016\n-1 0 0.000000016\n0 -1 0.000000016");
	fclose(input);
}