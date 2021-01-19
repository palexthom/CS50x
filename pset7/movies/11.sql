SELECT mv.title
FROM movies AS mv
    INNER JOIN stars as st ON mv.id = st.movie_id
    INNER JOIN people as pp ON st.person_id = pp.id
    INNER JOIN ratings as ra ON ra.movie_id = mv.id
WHERE pp.name = 'Chadwick Boseman'
ORDER BY ra.rating DESC
LIMIT 5