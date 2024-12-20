SELECT
  people.name
FROM
  people
WHERE
  people.id IN (
    SELECT
      stars.person_id
    FROM
      stars
    WHERE
      stars.movie_id = (
        SELECT
          movies.id
        FROM
          movies
        WHERE
          movies.title LIKE '%Toy Story%'
      )
  );