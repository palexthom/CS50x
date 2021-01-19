SELECT DISTINCT pp.name
FROM people AS pp
    INNER JOIN directors as di ON pp.id = di.person_id
    INNER JOIN movies as mv ON di.movie_id = mv.id
    INNER JOIN ratings as ra ON ra.movie_id = mv.id
WHERE ra.rating >= 9