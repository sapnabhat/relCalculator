# relCalculator

A file, companies.dat, contains a list of company names on each line. Company names may have multiple words in the name. Sometimes, a company might have multiple names associated with it. The first name is the primary name, and the remainder are synonyms. In this case, the company names will be separated by a tab on the same line. 

This program reads a news article from standard input. It reads until it gets a line in the article that consists entirely of a period symbol (.).

It identifies each company name in the article, and displays each company name on the screen, one line at a time. It always displays the primary name of the company identified, not the synonym. On the same line, it displays the "relevance" of the company name hit (Relevance is defined as frequency of the company name appearing in the article divided by the number of words in the article)." For example, Microsoft in "Microsoft released new products today." will result in a relevance of 1/5, or 20%. The relevance is in percentage. If two names for the same company match, they count as matches for the same one company. We ignore the following words in the article (but not the company name) when considering relevance: a, an, the, and, or, but

The company name search is normalized and punctuation and other symbols will not impact the search. So the appearance of Microsoft Corporation, Inc. in the companies.dat file will match with Microsoft Corporation Inc in the article. The search is case sensitive.
