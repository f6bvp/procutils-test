#!/bin/sh
#
# Script de bootstrap pour procax25.
# Lance la séquence Autotools pour générer le script 'configure'.
#
# Bootstrap script for procax25.
# Runs the Autotools sequence to generate the 'configure' script.
#

echo "Lancement de la séquence de bootstrap (Autotools)..."
echo "Starting Autotools bootstrap sequence..."

# 1. Nettoyage initial (facultatif mais recommandé pour éviter les caches obsolètes)
# Initial cleanup (optional but recommended to avoid stale caches)
rm -rf autom4te.cache aclocal.m4 configure config.status config.log Makefile.in

# 2. Générer aclocal.m4 à partir de configure.ac et des macros M4
# Generate aclocal.m4 from configure.ac and M4 macros
echo "Exécution de aclocal..."
echo "Running aclocal..."
aclocal || { echo "Erreur: aclocal a échoué. (Error: aclocal failed.)"; exit 1; }

# 3. Générer configure à partir de configure.ac
# Generate configure from configure.ac
echo "Exécution de autoconf..."
echo "Running autoconf..."
autoconf || { echo "Erreur: autoconf a échoué. (Error: autoconf failed.)"; exit 1; }

# 4. Générer Makefile.in à partir de Makefile.am
# Generate Makefile.in from Makefile.am
echo "Exécution de automake..."
echo "Running automake..."
automake --add-missing --copy || { echo "Erreur: automake a échoué. (Error: automake failed.)"; exit 1; }

echo ""
echo "Le script 'configure' est maintenant prêt."
echo "The 'configure' script is now ready."
echo "Prochaine étape : ./configure"
echo "Next step: ./configure"

exit 0

