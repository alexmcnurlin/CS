## Notes
  1. This is a bit easier than expected. The Auxilary functions (finding min/max and counting items in hash table) can be copied/modified from the code given
  2. Hash tables are fast!!!

  Effects of hash table size
    Size 7159:
      * Time: 0.061
      * Empty buckets: 0
    Size 11037:
      * Time: 0.066
      * Empty buckets: 50
    Size 49937:
      * Time: 0.210
      * Empty buckets: 15448
    Size 100:
      * Time: 0.307
      * Empty buckets: 0

## Difficulties
  1. The code given appears to use a lot of c syntax ( i.e. malloc ), so it's hard to understand some of it
  2. The table seems to add an empty entry to the first bucket when an empty file is given. Not a significant issue.
