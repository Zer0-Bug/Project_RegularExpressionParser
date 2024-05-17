# Regular Expression Parser

## Overview

This project implements a Regular Expression (Regex) Parser in the C programming language. The parser supports a comprehensive set of regex meta-characters, escape sequences, and various matching patterns to enable sophisticated string matching capabilities.

## Features

### Meta Characters

- **Parentheses `()`**: Grouping of expressions.
- **Square Brackets `[]`**: Specifies a character class.
- **Curly Braces `{}`**: Specifies a quantifier.
- **Caret `^`**: Indicates the start of a line.
- **Dollar `$`**: Indicates the end of a line.
- **Dot `.`**: Matches any character except a newline.
- **Backslash `\`**: Used for escaping meta-characters.

### Escape Character

- **Escape Character `\`**: Used to escape meta-characters.

### Character Classes

- **Within Square Brackets `[ ]`**: Specify a set of characters to match.

### Quantifiers

- **Question Mark `?`**: Matches zero or one occurrences of the preceding element.
- **Asterisk `*`**: Matches zero or more occurrences of the preceding element.
- **Plus Sign `+`**: Matches one or more occurrences of the preceding element.
- **Curly Braces `{}`**: Specify a specific number of occurrences or a range.

### Alternation

- **Vertical Bar `|`**: Indicates alternation, allowing for multiple possible matches.

## Examples

- `hello contains {hello}`
- `gray|grey contains {gray, grey}`
- `gr(a|e)y contains {gray, grey}`
- `gr[ae]y contains {gray, grey}`
- `b[aeiou]bble contains {babble, bebble, bibble, bobble, bubble}`
- `[b-chm-pP]at|ot contains {bat, cat, hat, mat, nat, oat, pat, Pat, ot}`
- `[a-zA-Z]` matches any lowercase or uppercase letter.
- `colou?r contains {color, colour}`
- `rege(x(es)?|xps?) contains {regex, regexes, regexp, regexps}`
- `go*gle contains {ggle, gogle, google, gooogle, goooogle, ...}`
- `go+gle contains {gogle, google, gooogle, goooogle, ...}`
- `g(oog)+le contains {google, googoogle, googoogoogle, googoogoogoogle, ...}`
- `z{3} contains {zzz}`
- `z{3,6} contains {zzz, zzzz, zzzzz, zzzzzz}`
- `z{3,} contains {zzz, zzzz, zzzzz, ...}`
- `[Gg]o\*\*le contains {Go**le, go**le}`
- `\d` matches any digit.
- `1\d{10}` matches an 11-digit string starting with a 1.
- `Hello\nworld contains Hello followed by a newline followed by world`
- `mi.....ft` contains a nine-character substring beginning with "mi" and ending with "ft".
- `^dog` begins with "dog".
- `dog$` ends with "dog".
- `^dog$` is exactly "dog".
- `[^i*&2@]` matches any character other than "i", "*", "&", "2", or "@".
- `([A-Z])\w+` finds all words starting with an uppercase letter.

## Usage

1. Clone the repository.
2. Compile the source code using a C compiler.
3. Run the compiled executable with appropriate input strings to test the regex patterns.

## Contribution

Contributions to improve and extend the functionality of this Regular Expression Parser are welcome. Please fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).