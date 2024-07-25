# BSD 3-Clause License
#
# Copyright (c) 2024, Christian Hennes
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#!/bin/bash

# Überprüfen, ob mindestens ein Argument übergeben wurde
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 [-f] <query>"
    exit 1
fi

# Variablen initialisieren
full_output=false
query=""

# Argumente überprüfen und zuweisen
if [ "$1" == "-f" ]; then
    full_output=true
    query=$2
elif [ "$2" == "-f" ]; then
    full_output=true
    query=$1
else
    query=$1
fi

# Überprüfen, ob das query-Argument leer ist
if [ -z "$query" ]; then
    echo "Usage: $0 [-f] <query>"
    exit 1
fi

# curl-Abfrage ausführen und Ergebnis speichern
response=$(curl -s cheat.sh/$query)

# Wenn -f als Parameter übergeben wurde, die gesamte Antwort ausgeben
if [ "$full_output" = true ]; then
    echo "$response"
else
    # Überprüfen, ob "tldr:" in der Antwort enthalten ist
    if echo "$response" | grep -q "tldr:"; then
        # Den Teil ab "tldr:" ausgeben
        echo "$response" | awk '/tldr:/ {flag=1} flag'
    else
        # Die gesamte Antwort ausgeben
        echo "$response"
    fi
fi

