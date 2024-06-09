# Electric potential 2D simulation with multithreading

This program simulates the electric potential field of a given situation of charged particles in 2D space.
It uses 4 threads, and gives each thread 1/4 of the total work. The result of each process is then combined and written into a file.

## Usage

`ElectricPotential2DMultithread -h`

>Shows information about the program and links to this page.

`ElectricPotential2DMultithread -a`

>Automatically creates a new input file `in.txt` with 3 charged particles as a demonstration, and then outputs the resulting field into a a text file named `out.txt`

`ElectricPotential2DMultithread -o [input_filename] [output_filename]`

>Takes the positions and charges from `input_filename` and outputs the final potential field into `output_filename.`
The input file must be in the format:
```
sizeX sizeY scaleX scaleY
x1 x1 q1
x2 y2 q2
...
```
The output file is in the format:
```
x1 y1 phi1
x2 y2 phi2
...
```
## Gallery
These are graphs of the output files, created using OriginLab.
![Image 1](https://github.com/TheNumber5/electric-potential-2d-multithread/assets/30901594/52380ac9-6e25-48ee-a75f-9824ea1352c6)
![Image 2](https://github.com/TheNumber5/electric-potential-2d-multithread/assets/30901594/2d2c7584-3583-4c71-b620-5b1f31ce69ba)
![Image 3](https://github.com/TheNumber5/electric-potential-2d-multithread/assets/30901594/0de960ac-4069-44e5-b65f-d906d53a6648)
