# Advance-Programming-Homework
This repository contains all of my homeworks in **Advance Programming** course at AmirKabir University of Technology.
<br>Instructor: Dr.Amir Jahanshahi
<br>Teacher Assistant: Mohammad Hossein Amini
## Attention
**C++ Standard**: C++23
<br>**Compiler**: GCC 12.0.2
<br>You can change versions in the **Makefile** and **Dockerfile**.
## Usage
Each assignment is contained in its own directory. To compile and run a specific assignment, navigate to the respective directory and use the following commands:
<br> 1.Open Docker Desktop.
<br> 2. Open WSL Ubuntu in your terminal of vscode.
<br> 3. Build the Docker Image with `docker build -t [tag_name] . `
<br> Replace `[tag_name]` with a suitable name for your docker image. 
<br> 4. After the image is built you can run it with: `docker run -v $PWD:/usr/src/app -it --rm [tag_name] /bin/bash` execute with `make && ./main`

