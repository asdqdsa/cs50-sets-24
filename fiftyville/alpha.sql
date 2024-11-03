-- .mode column
SELECT
  *
FROM
  passengers
  JOIN flights ON flight_id = flights.id
  JOIN airports ON flights.destination_airport_id = airports.id
WHERE
  passengers.passport_number = 3391710505;