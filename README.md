# vbsearch
This project is to extend binary search to non-scalar vectorized data. It based on “The software implementation of the vector data dichotomy” paper [1].
Binary and similar searching aptronyms are widely used and demonstrating the great performance O(log N). They are not directly applicable for vectors and other data that has no less/greater relation defined, unfortunately. Using linear search for relatively big sets of data has not a lot of sense. It is too slow O(N). 
This code implements the following algorithm:
- create function that will scalarize original vectors and satisfy two conditions: small number of collisions and reasonably small PCU consumptions
- sort original data using qsort or similar function using scalars calculated above. If no matches for scalars found it automatedly means that not matches for original vector found, so we are good
- if scalars matched there are extra steps require to define if this is a real or false match. Look around matched array element for exact vector match until scalar matched or array limits reached.

Performance results in compression with linear search:
Time required for scalarization and sorting is taken in to account for vsearch only (expected).
Standard qsort, bsearch and lfind routines and gcc complier from ubuntu 20.04 used. Size of array 1M complex elements.
- Collision probability 0%: efficiency (T linear / T vsearch) ~3.6K
- Collision probability 0.1%: efficiency (T linear / T vsearch) ~500
- Collision probability 1%: efficiency (T linear / T vsearch) ~60
- Collision probability 10%: efficiency (T linear / T vsearch) ~6
- Collision probability 100%: efficiency (T linear / T vsearch) ~25% slowly then linear srearch. Bad luck :-)

Regards, 
-	Andrey

[1] Proceedings of the (6th) Scientific Conference on Radiophysics devoted to the 100-th Anniversary of M.T.Grekhova's Birth. May 7, 2002. Ed. by A.V.Yakimov. Nizhni Novgorod. TALAM Press, 2002, 337 p.

