# TPE-arqui


### Development of the UserSpace of a basic computer

#### How to Setup environment to run
0. Install Docker (https://www.docker.com/) (https://docs.docker.com/engine/install/ubuntu/)
1. Download utilized image with `docker pull agodio/itba-so:1.0`
2. Change Directory into the directory with the TPE. That will be the directory associated with /root in the container, so all changes in that directory will be reflected in the container and vice versa.
3. run `docker run -d -v ${PWD}:/root --security-opt seccomp:unconfined -ti --name NOMBRE agodio/itba-so:1.0` where NAME refers to the name we are going to give to the container. The idea is to reuse it in development. However, if you want to create a container every time you want to use it, you will need to run: `docker run --rm -v ${PWD}:/root --security-opt seccomp:unconfined -ti agodio/itba-so:1.0` (Personally recommend this seccond option and running `exit` whenever done using the OS)
4. Enter the container environment. Although it is not necessary to do it right after decrypting, we usually first have to start the container by running the following (if we gave it a name): `docker start NAME`. Then, to enter the container terminal, we have to run `docker exec -ti NAME bash` Then, go to the project: `cd /root`
5. From /root, we'll have to set up the environment (Compiling and Linkediting files)

5.1 - Install the following packages before building the Toolchain and Kernel:

nasm, qemu, gcc, make

5.2 - Build the Toolchain
  Execute the following commands on the x64BareBones project directory:

  $> cd Toolchain
  $> make all

5.3 - Build the Kernel
  From the x64BareBones project directory run:

  {$> cd .. _(we need to be in /root)_}
  $> make all

5.4 - Run the kernel
  From the x64BareBones project directory run:

  $> ./run.sh
  (perhaps run.sh has to be modified by adding a sudo if ran in linux or/and running the command 'sed -i -e 's/\r$//' run.sh')

