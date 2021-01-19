SELECT pp.name
FROM movies as mv
    INNER JOIN stars as st ON st.movie_id = mv.id
    INNER JOIN people as pp ON st.person_id = pp.id
WHERE title='Toy Story'