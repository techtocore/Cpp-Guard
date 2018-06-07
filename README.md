# Cpp Guard

This is a native C++ code obfuscator that scrambles C++ source code to make it very difficult to understand or reverse-engineer, while still keeping the execution and control flow intact. 

This shall provide significant protection for source code intellectual property, or help in testing behavioral based anti malware engines. 

## Features

1. Strips single/multi line comments
2. Adding a pseudo-complex junk code snippet, while not affecting the asymptotic complexity of the overall program
3. Removing leading white-space
4. Removing line breaks
5. Handling all preprocessor directives, 'using' declarations and single-line 'else' clauses where the braces have been omitted.

## Todo

1. Optimize stripping of comments using regex
2. Implement renaming of variables
3. Change string encoding type
