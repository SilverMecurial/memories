SELECT name FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
WHERE movie_id IN (SELECT id FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0))