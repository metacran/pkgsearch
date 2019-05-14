## Search CRAN packages with pkgsearch

For search of CRAN packages, pkgsearch uses a [web service](https://github.com/metacran/search),
and a careful weighting that ranks popular packages before less
frequently used ones.

Use `pkg_search()` to search for a term or phrase:

```{r}
library(pkgsearch)
pkg_search("C++")
```

By default it returns a short summary of the ten best search hits. Their
details can be printed by using the `format = "long"` option of `pkg_search()`,
or just calling `pkg_search()` again, without any arguments, after a search:


```{r}
pkg_search()
```

The `more()` function can be used to display the next batch of search hits,
batches contain ten packages by default. `ps()` is shorter alias to
`pkg_search()`:

```{r}
ps("google")
```

```{r}
more()
```

## Features

In addition to simple text matching the search server and client have
many improvements to deliver better results.

### Stemming

The search server uses the stems of the words in the indexed metadata, and
the search phrase. This means that "colour" and "colours" deliver the
exact same result. So do "coloring", "colored", etc. (Unless one is happen
to be an exact package name or match another non-stemmed field.)

```{r}
ps("colour", size = 3)
ps("colours", size = 3)
```

### Ranking

The most important feature of a search engine is the ranking of the results.
The best results should be listed first. pkgsearch uses weighted scoring,
where a match in the package title gets a higher score than a match in the
package desciption. It also uses the number of reverse dependencies and
the number of downloads to weight the scores:

```{r}
ps("colour")[, c("score", "package", "revdeps", "downloads_last_month")]
```

### Preferring Phrases

The search engine prefers matching whole phrases over single words.
E.g. the search phrase "permutation test" will rank coin higher than
testthat, even though testthat is a much better result for the single word
"test". (In fact, at the time of writing testhat is not even on the first
page of results.)

```{r}
ps("permutation test")
```

If the whole phrase does not match, pkgsearch falls back to individual
matching words. For example, a match from either words is enough here,
to get on the first page of results:

```{r}
ps("test http")
```

### British vs American English

The seach engine uses a dictionary to make sure that package metadata
and queries given in British and American English yield the same results.
E.g. note the spelling of colour/color in the results:

```{r}
ps("colour")
ps("color")
```

### Ascii Folding

Especially when searching for package maintainer names, it is convenient
to use the corresponding ASCII letters for non-ASCII characters in search
phrases. E.g. the following two queries yield the same results. Note that
case is also ignored.

```{r}
ps("gabor", size = 5)
ps("Gábor", size = 5)
```