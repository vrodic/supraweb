/*
 * stringtok.h -- Breaks a string into tokens.  This is an example for lib3.
 *
 * Template function looks like this:
 *
 *    template <typename Container>
 *    void stringtok (Container &l,
 *                    string const &s,
 *                    char const * const ws = " \t\n");
 *
 * A nondestructive version of strtok() that handles its own memory and can
 * be broken up by any character(s).  Does all the work at once rather than
 * in an invocation loop like strtok() requires.
 *
 * Container is any type that supports push_back(a_string), although using
 * list<string> and deque<string> are indicated due to their O(1) push_back.
 * (I prefer deque<> because op[]/at() is available as well.)  The first
 * parameter references an existing Container.
 *
 * s is the string to be tokenized.  From the parameter declaration, it can
 * be seen that s is not affected.  Since references-to-const may refer to
 * temporaries, you could use stringtok(some_container, readline("")) when
 * using the GNU readline library.
 *
 * The final parameter is an array of characters that serve as whitespace.
 * Whitespace characters default to one or more of tab, space, and newline,
 * in any combination.
 *
 * 'l' need not be empty on entry.  On return, 'l' will have the token
 * strings appended.
 *
 *
 * [Example:
 *       list<string>       ls;
 *       stringtok (ls, " this  \t is\t\n  a test  ");
 *       for (list<string>::const_iterator i = ls.begin();
 *            i != ls.end(); ++i)
 *       {
 *            cerr << ':' << (*i) << ":\n";
 *       }
 *
 *  would print
 *       :this:
 *       :is:
 *       :a:
 *       :test:
 * -end example]
 *
 * pedwards@jaj.com  May 1999
*/


#include <string>
#include <cstring>    // for strchr


/*****************************************************************
 * This is the only part of the implementation that I don't like.
 * It can probably be improved upon by the reader...
*/
namespace {
    inline bool
    isws (char c, char const * const wstr)
    {
        return (strchr(wstr,c) != NULL);
    }
}


/*****************************************************************
 * Simplistic and quite Standard, but a bit slow.  This should be
 * templatized on basic_string instead, or on a more generic StringT
 * that just happens to support ::size_type, .substr(), and so on.
 * I had hoped that "whitespace" would be a trait, but it isn't, so
 * the user must supply it.  Enh, this lets them break up strings on
 * different things easier than traits would anyhow.
*/
template <typename Container>
void
stringtok (Container &l, string const &s, char const * const ws = " \t\n")
{
    const string::size_type  S = s.size();
          string::size_type  i = 0;

    while (i < S) {
        // eat leading whitespace
        while ((i < S) && (isws(s[i],ws)))  ++i;
        if (i == S)  return;  // nothing left but WS

        // find end of word
        string::size_type  j = i+1;
        while ((j < S) && (!isws(s[j],ws)))  ++j;

        // add word
        l.push_back(s.substr(i,j-i));

        // set up for next loop
        i = j+1;
    }
}
