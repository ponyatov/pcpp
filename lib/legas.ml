let app = Sys.getcwd () |> String.split_on_char '/' |> List.rev |> List.hd
let title = "PcapPlusPlus"

let about =
  "
[PcapPlusPlus](https://pcapplusplus.github.io/) is a multiplatform C++ library
for capturing, parsing and crafting of network packets. It is designed to be
efficient, powerful and easy to use.
"

let author = "Dmitry Ponyatov"
let email = "dponyatov@gmail.com"
let year = 2025
let license = "MIT"
let github = "github: https://github.com/ponyatov/" ^ app
let orig = "https://github.com/seladb/PcapPlusPlus.git"
let tag = "v25.05"
