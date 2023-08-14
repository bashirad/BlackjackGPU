# Current_CUDA_BCG

## Blackjack GPU Learning Project
## Blackjack

Welcome to the Blackjack GPU Learning project! This research project focuses on using the power of the GPU (Graphics Processing Unit) to learn and play Blackjack optimally.

  ## Table of Contents
  ### 1. Project Overview
  ### 2. Installation
  ### 3. Usage
  ### 4. Contributing
  ### 5. License

## Project Overview
The main goal of this project is to utilize the computational power of the GPU to train a model that can play Blackjack (also known as 21) optimally. Blackjack is a popular card game played between a player and a dealer. The objective of the game is to reach a hand value of 21 or as close to it as possible, without exceeding 21.

Traditionally, reinforcement learning algorithms for games have been implemented on CPUs (Central Processing Units). However, GPUs offer parallel processing capabilities that can significantly speed up the training process. This project aims to explore the potential benefits of GPU acceleration for learning to play Blackjack.

## Installation
To get started with the project, follow these installation instructions:

Clone the repository to your local machine using the following command:

git clone https://github.com/bashirad/Current_CUDA_BCG.git

Install the necessary dependencies. Make sure you have the following software installed:

### Visual Studio 2022 
### CUDA toolkit version 11.7
### NVIDIA GPU driver

## Usage
Before running the project, ensure that you have a compatible NVIDIA GPU and the required software installed. Here are the basic steps to use the project:

Open the Visual Studio project solution file with extension (.sln) = Current_CUDA_BCG.sln.

Run the Main file to start training the Blackjack model on the GPU:

The training process will utilize the GPU for accelerated computations. The script will output progress updates, training statistics, and save the trained model for future use.

Once the training is complete, you can evaluate the performance of the model by running the evaluation script:

The evaluation script will simulate Blackjack games using the trained model and provide performance metrics and insights.

Feel free to explore the codebase, experiment with different hyperparameters, or modify the implementation to suit your needs.

## Contributing
Contributions to this project are always welcome. If you'd like to contribute, please follow these steps:

Fork the repository on GitHub.
1. Create a new branch from the main branch for your feature or bug fix.
2. Make your changes and commit them with descriptive commit messages.
3. Push your changes to your forked repository.
4. Submit a pull request to the original repository, describing your changes in detail.
5. Please ensure that your code follows the project's coding style and conventions. Also, consider adding tests and updating the documentation if necessary.

## License
Copyright (c) Ron Coleman, and Bashir Dahir
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Acknowledgements
We would like to express our gratitude to the open-source community for providing valuable resources, libraries, and frameworks that made this project possible. Your contributions are greatly appreciated.

If you have any questions or feedback regarding the project, please don't hesitate to contact us. Enjoy playing Blackjack with GPU acceleration!
