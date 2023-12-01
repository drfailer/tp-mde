# TP 5

## Compilation

1. Installer CLHEP:

```sh
git submodule init
git submodule sync
git submodule update
cd lib
./build.sh
```

2. Compiler le tp:

```sh
mkdir build
cd build
cmake ..
make
```

## Usage

```sh
# génération des fichiers de status (question 3, à lancer obligatoirement)
./tp5

# test répétabilité du générateur (question 2)
./tp5 test

# calcul de pi
./tp5 pi     # calcul de pi en séquentiel (question 4)
./tp5 pi par # calcul de pi en parallèle (question 6a)

# gattaca
./tp5 gattaca gen # génération des fichiers de status pour gattaca (optionel, ne
                  # sert que s'il on a modifier la configuration du programme).
./tp5 gattaca # génération du mot gattaca
```

### Script `compute_pi.sh`

Le script permet le calcul de $\pi$ en parallèle sans utiliser les threads.
