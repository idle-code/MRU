cmake_minimum_required (VERSION 2.8)

add_library (MetatagExpressionTokenizer "Tokenizer.cpp")
target_link_libraries (MetatagExpressionTokenizer TokenizerBase ${LIBS})

add_library (MetatagExpressionLexer "Lexer.cpp")
target_link_libraries (MetatagExpressionLexer MetatagExpressionTokenizer ${LIBS})

add_library (MetatagExpressionParser "Parser.cpp")
target_link_libraries (MetatagExpressionParser MetatagExpressionLexer ${LIBS})

add_library (MetatagExpression "Expression.cpp")
target_link_libraries (MetatagExpression MetatagBase MetatagExpressionParser ${LIBS})

