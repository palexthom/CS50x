SELECT pp.name
FROM people AS pp
    INNER JOIN stars as st ON pp.id = st.person_id
    INNER JOIN movies as mv ON st.movie_id = mv.id
WHERE mv.year = 2004
ORDER BY pp.birth ASC