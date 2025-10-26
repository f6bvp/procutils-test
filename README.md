🎯 Objective (Objectif)

The main purpose of the procax25 application is to verify, validate, and demonstrate the correct usage of the parsing functions contained within the procutils.c module of the AX.25 library.

This program is a simple diagnostic and testing utility, designed to read and display the state information of AX.25 connections exposed by the Linux kernel via the virtual file /proc/net/ax25.

✨ Key Features (Fonctionnalités Clés)

    Reading /proc/net/ax25: Uses the read_proc_ax25() function (from procutils.c) to retrieve the complete list of active AX.25 connections.

    Standardized Display: Formats the data into a clear, readable table, facilitating the interpretation of fields (MAGIC, DEV, SRC, DEST, Timers, RTT, etc.).

    Format Support: Confirms whether the /proc/net/ax25 output includes the new header (the format we implemented) or uses the old format without a header.

    Reversed Order: Displays connections in the reverse order of reading the /proc file, placing the most recent or most relevant connections at the top of the list.

🔗 Dependencies (Dépendances)

This program depends on the AX.25 library for compilation and execution. Specifically, it requires:

    The header file <netax25/procutils.h> and other headers from the AX.25 package.

    The libax25 library for linking.

🚀 Quick Installation and Compilation (Installation Rapide)

This package uses GNU Autotools for configuration. For detailed instructions, please refer to the INSTALL file.

    Preparation: Run ./bootstrap.sh if the configure script is missing (required after make distclean or a fresh Git clone).

    Configuration:
    Bash

$ ./configure

Compilation:
Bash

$ make

Execution: The procax25 executable will be created and can be run directly:
Bash

    $ ./procax25

👤 Author and License (Auteur et Licence)

    Author: Bernard Pidoux (F6BVP / AI7BG)

    License: This program is distributed under the terms of the GNU General Public License, version 2.0 (GPLv2) for Linux.
