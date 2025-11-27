# host language
## [[implementation language]]
![[source-to-source translation]]

[[host language]] is a [[lang/programming language|programming language]] on which **[[metasystem]]** must be implemented as a set of libraries for 
- [[syntax/parsing|syntax parsing]]
	- [[parser generator]]s or dynamic parser builders
- analysis passes from some [[compiler]] stages, including
	- [[Semantic Analysis]]
	- [[Dataflow]] analysis 
- structural [[uml/diagram|diagrams]] generators
	- for [[sw/code documenting|code documenting]] and redesign

## requirements

- [[lang/REPL|REPL]] & interpretation mode
	> the main approach of working with [[legas]] is a dialog command console runs in [[vscode/VSCode|VSCode]] internal terminal (sending selected script fragments with Shift-Enter/Ctrl-Enter and looking on REPL output and generated files)
- highest-level abstractions
	- rich macro subsystem for [[lang/DSL|eDSL]] design
	- [[oop/OOP|OOP]] paradigm (maybe [[lang/FP|FP]] is better for source code analysis domain?)
	- off the shelf tools for making arbitrary [[syntax/parser|syntax parsers]] and [[lang/DSL|DSLs]]
- **[[lang/pattern matching|pattern matching]]**
	- [[host language]] should has [[type/datatype|datatypes]] and
	- strongly typed
	- but [[dynamic typing]] allowed

## candidates

- **[[OCaml/OCaml|OCaml]] was [[#selected]]**
- other variants
	- [[Fsh|F#]]
	- [[Python]]
- looks too complex and publicly unfamiliar:
	- [[Haskell]]
	- [[Elixir]]

## selected

[[OCaml/OCaml|OCaml]] was selected to be used as [[host language]] due to 
- known as good candidate for compiler developement: [[legas/bib]]
- off-the-shelf tools for syntax parser generation
- rich macro & DSL support
- 
