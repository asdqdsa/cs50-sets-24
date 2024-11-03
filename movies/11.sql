.mode column
SELECT movies.title
FROM 
  ratings
  JOIN movies ON ratings.movie_id = movies.id
WHERE movies.id IN 
(SELECT
  id
FROM
  movies
WHERE
  movies.id IN (
    -- ID's list of Boseman movies
    SELECT
      stars.movie_id
    FROM
      stars
    WHERE
      stars.person_id = (
        -- ID Chadwick Boseman
        SELECT
          people.id
        FROM
          people
        WHERE
          people.name LIKE '%Chadwick Boseman%'
      )
  ) 
) ORDER BY rating DESC LIMIT 5
--JOIN ratings ON movies.id = ratings.movie_id;
-- ORDER BY
--   ratings.rating ASC;