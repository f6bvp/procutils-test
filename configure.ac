# Fichier : configure.ac

# 1. INITIALISATION (avec AC_INIT)
AC_INIT([procax25], [1.0], [f6bvp@free.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# 2. VÉRIFICATION DU COMPILATEUR C (Résout les erreurs _AC_LANG)
AC_PROG_CC

# 3. VÉRIFICATION DE LA LIBRAIRIE AX25 (Avec Logique de Secours)

# Tenter d'abord la recherche standard via pkg-config (préférable)
PKG_CHECK_MODULES([AX25], [ax25-config], [has_ax25_pkg=yes], [has_ax25_pkg=no])

# Si pkg-config échoue, configurer manuellement pour l'installation locale/standard
AS_IF([test "x$has_ax25_pkg" = "xno"], [
    AC_MSG_NOTICE([Package 'ax25-config' not found. Trying to manually locate AX25 headers and libraries.])
    
    # Définir les chemins basés sur l'emplacement trouvé :
    # Headers (/usr/include/netax25/ax25.h) -> -I/usr/include
    AX25_CFLAGS="-I/usr/include"
    # Librairies (/usr/local/lib/libax25.so) -> -L/usr/local/lib -lax25
    AX25_LIBS="-L/usr/local/lib -lax25"
    
    # Vérifier l'existence du fichier d'en-tête
    AC_CHECK_HEADER([netax25/ax25.h], [], [
        AC_MSG_ERROR([AX25 headers (netax25/ax25.h) not found. Please check your installation.])
    ])

    # S'assurer que les variables sont transmises au Makefile
    AC_SUBST([AX25_CFLAGS])
    # Substitution pour correspondre à $(AX25_LIB) dans Makefile.am
    AC_SUBST([AX25_LIB], [$AX25_LIBS])
])

# 4. GÉNÉRATION DES FICHIERS DE SORTIE (Résout l'avertissement AC_OUTPUT)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
