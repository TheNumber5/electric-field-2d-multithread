#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <math.h>
#include "Information.h"

#define k 8.99*pow(10, 9)

//Program that calculates the electric potentials of a field of charged particles.
//It uses 4 independent threads, each one doing 1/4 of the work, and then the result is assembled in one final structure and outputted.
//Version: v1.0
//Date: 09/06/2024

int sizeX, sizeY;
float scaleX, scaleY;

struct Particle {
	float x, y, q;
};

struct Point {
	float x, y, phi;
};

struct Info {
	struct Particle *pa;
	struct Point *po;
	unsigned int num, xStart, yStart, factoryNumber;
};

void calcPotential(struct Particle particle, struct Point *fieldPoint) {
	float dist = sqrt((pow(particle.x-fieldPoint->x, 2)+pow(particle.y-fieldPoint->y, 2)));
	if(dist>0.01) {
		float phi = k*particle.q/dist;
		fieldPoint->phi += phi;
	}
}

unsigned int factoryEnd = 0;
long currentIndex=0;

void factory(void *p) {
	struct Info *data = (struct Info*)p;
	for(int h=0; h<data->num; h++)
		for(int j=data->yStart; j<sizeY/2+data->yStart; j++) {
		for(int i=data->xStart; i<sizeX/2+data->xStart; i++) {
			unsigned int index = i*sizeY+j;
			calcPotential(data->pa[h], &data->po[index]);
			if(data->factoryNumber==0) {
			currentIndex++;
			if(currentIndex%100000==0)
				printf("Current Index: %ld/%ld\n", currentIndex, data->num*sizeX*sizeY/4);
			}
	}
	}
	factoryEnd++;
	_endthread();
}

int main(int argc, char **argv) {
	char inFile[15], outFile[15];
	FILE *input, *output;
	if (argc>1) {
	if(!strcmp(argv[1], "-h")) {
		ShowInformation();
		return 0;
	}
	else if(!strcmp(argv[1], "-a")) {
		CreateNewFile();
		input = fopen("in.txt", "rb");
		output = fopen("out.txt", "wb");
	}
	else if(!strcmp(argv[1], "-o")) {
		input = fopen(argv[2], "rb");
		output = fopen(argv[3], "wb");
	}
	else {
		printf("Unknown command. Use -h for help.");
		return 0;
	}
	}
	else {
		ShowInformation();
		return 0;
	}
	char ch;
	unsigned int num = 0;
	while((ch=fgetc(input))!=EOF) {
		if(ch=='\n')
			num++;
	}
	fseek(input, 0, SEEK_SET);
	fscanf(input, "%d %d %f %f", &sizeX, &sizeY, &scaleX, &scaleY);
	struct Point *field = (struct Point*)malloc(sizeX*sizeY*sizeof(struct Point));
	struct Particle particles[num];
	for(int i=0; i<num; i++)
		fscanf(input, "%f %f %f", &particles[i].x, &particles[i].y, &particles[i].q);
	for(int i=0; i<sizeX; i++) {
		for(int j=0; j<sizeY; j++) {
			unsigned int index = j*sizeY+i;
			field[index].x = ((float)i-(float)sizeX/2.0)/scaleX;
			field[index].y = ((float)j-(float)sizeY/2.0)/scaleY;
			field[index].phi = 0;
		}
	}
	struct Info info[4];
	for(int i=0; i<4; i++) {
		info[i].factoryNumber = i;
		info[i].pa = &particles[0];
		info[i].po = field;
		info[i].num = num;
		info[i].xStart = i%2*sizeX/2;
		info[i].yStart = i/2*sizeY/2;
		_beginthread(factory, 0, &info[i]);
	}
	do {
		Sleep(100);
	} while(factoryEnd<4);
	printf("Calculation done\n");
	for(int i=0; i<sizeX; i++) {
		for(int j=0; j<sizeY; j++) {
			unsigned int index = j*sizeY+i;
			fprintf(output, "%0.3f %0.3f %0.10f\n", field[index].x, field[index].y, field[index].phi);
		}
	}
	fclose(output);
	fclose(input);
	return 0;
}