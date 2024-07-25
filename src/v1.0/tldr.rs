/*BSD 3-Clause License

Copyright (c) 2024, Christian Hennes

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

use std::env;
use std::process::Command;

fn fetch_cheat_sheet(query: &str, full_output: bool) {
    let output = Command::new("curl")
        .arg(format!("cheat.sh/{}", query))
        .output()
        .expect("Failed to execute curl");

    let response = String::from_utf8_lossy(&output.stdout);

    if full_output {
        println!("{}", response);
    } else {
        if let Some(tldr_start) = response.find("tldr:") {
            println!("{}", &response[tldr_start..]);
        } else {
            println!("{}", response);
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: tldr [-f] <application>");
        std::process::exit(1);
    }

    let mut full_output = false;
    let query: &str;

    if args[1] == "-f" {
        full_output = true;
        query = &args[2];
    } else if args.len() > 2 && args[2] == "-f" {
        full_output = true;
        query = &args[1];
    } else {
        query = &args[1];
    }

    fetch_cheat_sheet(query, full_output);
}

