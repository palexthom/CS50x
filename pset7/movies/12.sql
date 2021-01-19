SELECT mv.title
FROM movies AS mv
    INNER JOIN stars as st1 ON mv.id = st1.movie_id
    INNER JOIN stars as st2 ON mv.id = st2.movie_id
    INNER JOIN people as pp1 ON st1.person_id = pp1.id
    INNER JOIN people as pp2 ON st2.person_id = pp2.id
WHERE pp1.name = 'Johnny Depp' and pp2.name = 'Helena Bonham Carter'