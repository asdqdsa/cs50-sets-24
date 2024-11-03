SELECT
  movies.title
FROM
  movies
WHERE
  -- IDs with Bradley Cooper
  movies.id IN (
    SELECT
      stars.movie_id
    FROM
      stars
    WHERE
      stars.person_id = (
        SELECT
          people.id
        FROM
          people
        WHERE
          people.name = 'Bradley Cooper'
      )
  )
  -- IDs with Jennifer Lawrence
  AND movies.id IN (
    SELECT
      stars.movie_id
    FROM
      stars
    WHERE
      stars.person_id = (
        SELECT
          people.id
        FROM
          people
        WHERE
          people.name = 'Jennifer Lawrence'
      )
  );