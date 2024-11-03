-- NESTED solution
-- SELECT
--   AVG(rating)
-- FROM
--   ratings
-- WHERE
--   ratings.movie_id IN (
--     SELECT
--       movies.id
--     FROM
--       movies
--     WHERE
--       movies.year = 2012
--   );
-- JOIN solution
SELECT
  AVG(rating)
FROM
  ratings
  JOIN movies ON ratings.movie_id = movies.id
WHERE
  movies.year = 2012