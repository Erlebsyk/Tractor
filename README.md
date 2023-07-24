<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<br />
<br />
<div align="center">
  <a href="https://github.com/Erlebsyk/Tractor">
    <img src="https://raw.githubusercontent.com/Erlebsyk/Tractor/main/tractor/resources/images/logo_small.gif" alt="Logo" width="120" height="94">
  </a>

<h3 align="center">Tractor</h3>

  <p align="center">
    A simple game engine
    <br />
    <a href="https://github.com/Erlebsyk/Tractor"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Erlebsyk/Tractor">View Demo</a>
    ·
    <a href="https://github.com/Erlebsyk/Tractor/issues">Report Bug</a>
    ·
    <a href="https://github.com/Erlebsyk/Tractor/issues">Request Feature</a>
  </p>
  <br />
  <br />
	

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Apache License][license-shield]][license-url]
[![Issues][issues-shield]][issues-url]


</div>

<h1>Tractor</h1>



<!-- TABLE OF CONTENTS -->
<details open>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
<div id="about-the-project"></div>

## About The Project

This is a simple game engine created primarily for learning about the process of making a game engine, involving build systems, architecture and implementation. If the game engine proves to be efficient, additional features can be added such as fast physics, simulation etc. The engine is heavily inspired by the project "Hazel".

Some of the main planned features of the engine:
* Structured project setup with build system, tests and documentation.
* Input/Event system.
* Renderer (API).
* Debugging and benchmark tools.
* External script support.
* Memory systems.
* Entity-Component system.
* Physics.
* File I/O.
* Audio.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<div id="built-with"></div>

### Built With

* [![googletest][googletest]][googletest-url]
* [![OpenGL][opengl]][opengl-url]
* [![glm][glm]][glm-url]
* [![sdl][sdl]][sdl-url]
* [![doxygen][doxygen]][doxygen-url]
* [![graphviz][graphviz]][graphviz-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
<div id="getting-started"></div>

## Getting Started


<div id="prerequisites"></div>

### Prerequisites

This project is a C++ project that uses CMake as a make file. To build the project you need to have a C/C++ compiler that support C++17 and higher. For instance:
- [*Visual C++*](http://www.visualstudio.com/)
- [*GCC*](http://gcc.gnu.org/)
- [*Intel C++ Compose*](https://software.intel.com/en-us/intel-compilers)

Additionally, you will need the following tools to build the project:
- [*CMake*](https://cmake.org/download/) - To generate the build files you need to have CMake installed.
- [*Doxygen*](https://www.doxygen.nl/download.html) - To generate the documentation you need to have Doxygen installed.
- [*Graphviz*](https://graphviz.org/download/) - To generate the visualization for the documentation you need to have Graphviz installed.

Additional library dependencies are automatically included via. git submodules, and included in the project through CMake.

<div id="installation"></div>

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Erlebsyk/Tractor.git
   ```
2. Run CMake to generate build files.
3. Compile the code with a suited C/C++ compiler.

If CMake is able to find all prerequisites, the project should compile without any problems using the CMake Build task.


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
<div id="usage"></div>

## Usage

The project is currently in a very early stage of development and is not yet ready for use. The project is currently being developed on Windows 11 using Visual Studio Code. The project is not yet tested on other platforms.

To run tests, the google tests are integrated into the CMake build system and can be run using the CMake Test task.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ROADMAP -->
<div id="roadmap"></div>

## Roadmap

- [x] Structured project setup with build system, tests and documentation
- [x] Logging module
- [ ] Input/Event system
- [ ] Renderer
	- [ ] OpenGL
	- [ ] API
- [ ] Debugging and benchmark tools
- [ ] External script support
- [ ] Memory systems
- [ ] Entity-Component system
- [ ] Physics
- [ ] File I/O
- [ ] Audio

See the [open issues](https://github.com/Erlebsyk/Tractor/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
<div id="contributing"></div>

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
<div id="license"></div>

## License

Distributed under the Apache License. See `LICENSE` and `NOTICE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
<div id="contact"></div>

## Contact
Project Link: [https://github.com/Erlebsyk/Tractor](https://github.com/Erlebsyk/Tractor)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
<div id="acknowledgments"></div>

## Acknowledgments

* [Yan Chernikov](https://www.youtube.com/@TheCherno/featured) (The Cherno)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!-- Simple icons can be found at https://simpleicons.org/ --> 
[contributors-shield]: https://img.shields.io/github/contributors/Erlebsyk/Tractor.svg?style=for-the-badge
[contributors-url]: https://github.com/Erlebsyk/Tractor/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Erlebsyk/Tractor.svg?style=for-the-badge
[forks-url]: https://github.com/Erlebsyk/Tractor/network/members
[stars-shield]: https://img.shields.io/github/stars/Erlebsyk/Tractor.svg?style=for-the-badge
[stars-url]: https://github.com/Erlebsyk/Tractor/stargazers
[issues-shield]: https://img.shields.io/github/issues/Erlebsyk/Tractor.svg?style=for-the-badge
[issues-url]: https://github.com/Erlebsyk/Tractor/issues
[license-shield]: https://img.shields.io/github/license/Erlebsyk/Tractor.svg?style=for-the-badge
[license-url]: https://github.com/Erlebsyk/Tractor/blob/master/LICENSE.txt

[googletest]: https://img.shields.io/badge/googletest-35495E?style=for-the-badge&logo=Google&logoColor=4285F4
[googletest-url]: https://github.com/google/googletest

[opengl]: https://img.shields.io/badge/OpenGL-E8E8E8?style=for-the-badge&logo=OpenGL&logoColor=5586A4
[opengl-url]: https://www.opengl.org/
[glm]: https://img.shields.io/badge/glm-F36633?style=for-the-badge&logo=glm
[glm-url]: https://github.com/g-truc/glm
[sdl]: https://img.shields.io/badge/sdl-113155?style=for-the-badge&logo=sdl
[sdl-url]: https://github.com/libsdl-org/SDL
[doxygen]: https://img.shields.io/badge/doxygen-4285F4?style=for-the-badge&logo=doxygen
[doxygen-url]: https://www.doxygen.nl/
[graphviz]: https://img.shields.io/badge/graphviz-00005F?style=for-the-badge&logo=graphviz
[graphviz-url]: https://graphviz.org/