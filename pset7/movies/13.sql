SELECT pp2.name
FROM movies AS mv
    INNER JOIN stars as st1 ON mv.id = st1.movie_id
    INNER JOIN stars as st2 ON mv.id = st2.movie_id
    INNER JOIN people as pp1 ON st1.person_id = pp1.id
    INNER JOIN people as pp2 ON st2.person_id = pp2.id
WHERE pp1.name = 'Kevin Bacon' and pp2.name != 'Kevin Bacon'