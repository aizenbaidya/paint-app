# OpenGL Paint Application

This project is an interactive paint application inspired by Microsoft Paint, written in C++ and made with OpenGL. It has a simple UI and provides essential tools and features for painting.

## Features

- Paintbrush tool (draw points as a scribble).
- Eraser tool (delete shapes and scribbles).
- Screen clearing tool (delete all shapes and scribbles).
- RGB color picker.
- Four shape tools.
- Selector tool (ability to select a shape or scribble by clicking on it).
- Ability to bring the selected shape or scribble to the front.
- Ability to send the selected shape or scribble to the back.
- Ability to move the selected shape or scribble by dragging.
- Ability to change the color of the selected shape or scribble.

## Setup

1. Install [Visual Studio](https://visualstudio.microsoft.com/downloads/) and configure it for desktop development with C++.
2. Download [FreeGLUT 3.0.0 for Microsoft Visual C++](https://www.transmissionzero.co.uk/software/freeglut-devel/).
3. Download the [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) library.
4. Create a new project configured for C++ and your platform in Visual Studio.
5. Make a `dependencies` folder in your project's folder.
6. In the `dependencies` folder, copy and paste the extracted `freeglut` folder inside.
7. In `dependencies`, create a new folder called `stb`. Inside `stb`, create a new folder called `include`. Inside `include`, copy & paste the `stb_image.h` file inside.
8. Navigate to the project's properties and go to "VC++ Directories." Inside "Include Directories," add the directory location of `freeglut`'s `include` folder. Do the same for `stb`'s `include` folder.
9. Next, inside "Library Directories," add the directory location of `freeglut`'s `lib` folder's designated  platform (`Win32` or `x64`).
10. In "Linker," go to "Additional Dependencies" and add `freeglut.lib`.
11. Then, in "Build Events" &#8594; "Post-Build Events," add the following command in the "Command Line" section:\
    `copy "$(SolutionDir)dependencies\freeglut\bin\$(Platform)\freeglut.dll" "$(OutDir)"`
12. Finally, add the necessary code files and `assets` to "Source Files."

(For more help and clarification, please refer to the following tutorials listed in the "Credits.")

## Credits

The application leverages the [FreeGLUT](https://freeglut.sourceforge.net/) library to create the window, initialize OpenGL contexts, render graphics, and handle user input events. The [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) library loads images from local files into the program. The following tutorials on [setting up a FreeGLUT project in Visual Studio](https://www.youtube.com/watch?v=A1LqGsyl3C4&ab_channel=TechLearners) and [the installation process for stb_image.h](https://www.youtube.com/watch?v=Z4I_EEskNK4&ab_channel=MichaelGrieco) were extremely valuable in the project setup process.

## Side Notes

This program leverages pointers and dynamic memory allocation to manage data structures and prevent memory leaks to improve application performance.
