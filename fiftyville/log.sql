-- Keep a log of any SQL queries you execute as you solve the mystery.
-- .schema outline of the DB
-- 
-- KNOWN FACTS: 
-- took place on July 28, 2023, Humphrey Street.
-- TODO
-- check crime scene reports the day when the theft took place and found two entries
-- (optional)check all reports with Humphrey Street mentioned
-- (optional)check for duck, cs50 in description of all reports available
--
-- checking crime reports 
SELECT
  *
FROM
  crime_scene_reports
WHERE
  crime_scene_reports.year = 2023
  AND crime_scene_reports.month = 7
  AND crime_scene_reports.street LIKE '%Humphrey Street%'
  AND crime_scene_reports.day = 28;

-- KNOWN FACTS: 
-- took place on July 28, 2023, Humphrey Street, time 10:15am
-- three witnesses
-- ClUES: 
-- witnesses mention bakery
-- TODO
-- check interview transcripts word 'bakery'
-- (optional)check bakery security logs the day of the theft
--
-- checking interview transcripts
SELECT
  *
FROM
  interviews
WHERE
  interviews.transcript LIKE '%bakery%';

-- KNOWN FACTS:
-- took place on July 28, 2023, Humphrey Street, time 10:15am
-- three witnesses (Ruth, Eugene, Raymond)
-- bakery parking lot (Emma's bakery)
-- CLUES:
-- thief had a car
-- suspect withdrew money ATM, Leggett Street, morning
-- a brief phone call was made right after the robbery
-- suspect asked for earliest flight out of Fiftyville for tomorrow
-- someone else could've bought a ticket for the flight (possible accomplice)
-- TODO:
-- check Emma's bakery security footage/logs for car model/license plate around crime time
-- check ATM transactions between 5am - 10am, Leggett Street
-- (optional)check all flights for 29 of July 2023
--
-- checking Emma's bakery camera outside
SELECT
  bakery_security_logs.license_plate,
  bakery_security_logs.hour,
  bakery_security_logs.minute
FROM
  bakery_security_logs
WHERE
  bakery_security_logs.year = 2023
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute > 10
  AND bakery_security_logs.minute < 30
  AND bakery_security_logs.activity = 'exit';

-- checking ATM transactions 5am - 10am, Leggett Street
SELECT
  *
FROM
  atm_transactions
WHERE
  atm_transactions.year = 2023
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.transaction_type = 'withdraw'
  AND atm_transactions.atm_location LIKE '%Leggett Street%';

-- checking all flight for 29 of July
-- joining airports and flights tables by id for convenience
SELECT
  *
FROM
  flights
  JOIN airports ON flights.destination_airport_id = airports.id
WHERE
  flights.year = 2023
  AND flights.month = 7
  AND flights.day = 29
ORDER BY
  flights.hour;

-- KNOWN FACTS:
-- ...
-- 8 plates - 8 cars left parking lot in a span of 10 minutes
-- 8 atm acc. numbers for further investigation
-- 5 flights has happened on July 29
-- CLUES:
-- whoever out 8 people withdrew money could be on the flight on 29 as a passenger
-- whoever out 8 people withdrew money could use a phone match by caller name
-- TODO:
-- check atm acc number with bank db, get people ids
-- check by people ids their name, phone, etc.
-- to find matches by name, plate, phone numbers
-- checking by id bank db and get people personal info
SELECT
  *
FROM
  people
WHERE
  -- get people info by id received from bank
  people.id IN (
    SELECT
      bank_accounts.person_id
    FROM
      bank_accounts
    WHERE
      -- match accounts ids with people id DB bank
      bank_accounts.account_number IN (
        SELECT
          atm_transactions.account_number
        FROM
          atm_transactions
        WHERE
          atm_transactions.year = 2023
          AND atm_transactions.month = 7
          AND atm_transactions.day = 28
          AND atm_transactions.transaction_type = 'withdraw'
          AND atm_transactions.atm_location LIKE '%Leggett Street%'
      )
  );

-- CLUES:
-- 8 license plate numbers from each person that withdrew money from ATM on 28 of July
-- and their names, phone numbers, passports info
-- TODO:
-- search for matching plates from bakery parking lot and atm person of interest

-- identifying possible suspect by plates
SELECT
  *
FROM
  people
WHERE
  -- get people info by id received from bank
  people.id IN (
    SELECT
      bank_accounts.person_id
    FROM
      bank_accounts
    WHERE
      -- match accounts ids with people id DB bank
      bank_accounts.account_number IN (
        SELECT
          atm_transactions.account_number
        FROM
          atm_transactions
        WHERE
          atm_transactions.year = 2023
          AND atm_transactions.month = 7
          AND atm_transactions.day = 28
          AND atm_transactions.transaction_type = 'withdraw'
          AND atm_transactions.atm_location LIKE '%Leggett Street%'
      )
      -- matching all plates from the bakery parking lot
  ) AND people.license_plate IN (
    SELECT
  bakery_security_logs.license_plate
FROM
  bakery_security_logs
WHERE
  bakery_security_logs.year = 2023
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute > 10
  AND bakery_security_logs.minute < 30
  AND bakery_security_logs.activity = 'exit';
  );

-- CLUES:
-- 4 people info matching that left parking lot,
-- that withdrew money that morning from the ATM
-- TODO:
-- Check all passenger by passport number for each flight on 28th of July

-- checking 4 people on all flights the next day after the robbery
-- by passport numbers
-- 7049073643  8496433585  3592750733  5773159633
SELECT
  flights.id
FROM
  flights
WHERE
  flights.year = 2023
  AND flights.month = 7
  AND flights.day = 29
  AND flights.id IN (SELECT
  passengers.flight_id
FROM
  passengers
WHERE
  passengers.passport_number IN (7049073643, 8496433585, 3592750733, 5773159633))
ORDER BY
  flights.hour;
 
-- CLUES:
-- id flights 36, 18

-- filtering by flights.id
SELECT
  passengers.passport_number
FROM
  passengers JOIN flights ON passengers.flight_id = flights.id
WHERE
  passengers.passport_number IN (7049073643, 8496433585, 3592750733, 5773159633)
  AND passengers.flight_id IN (18, 36);

-- CLUES:
-- 3 people matching the day of the flight (29th) out of 4 that left parking lot on 28th
-- 3592750733 5773159633 8496433585
-- TODO:
-- check phone calls for number matching for each caller (Dian Bruce Luca)
-- find receiver number

-- filtering by caller number 
SELECT * FROM people
WHERE people.phone_number IN (SELECT
  phone_calls.caller
FROM
  phone_calls 
WHERE
  phone_calls.year =2023
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
  ORDER BY phone_calls.duration)
AND people.passport_number IN (8496433585, 3592750733, 5773159633);
-- CLUES:
-- Only Diana and Bruce made a call for less than a minute 
-- 514354  Diana  (770) 555-1861  3592750733
-- 686048  Bruce  (367) 555-5533  5773159633
-- TODO:
-- check receivers phone numbers and info in people
SELECT * FROM people
WHERE people.phone_number IN (SELECT
  phone_calls.receiver
FROM
  phone_calls 
WHERE
  phone_calls.year =2023
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
  AND phone_calls.caller IN ('(770) 555-1861', '(367) 555-5533')
  ORDER BY phone_calls.duration);

-- TWO PEOPLE WERE CALLING TO
-- 847116  Philip  (725) 555-3243  3391710505       GW362R6     
-- 864400  Robin   (375) 555-8161                   4V16VO0 
-- DIANA called Philip
-- BRUCE called Robin
-- Robin doesn't have a passport number
-- TODO:
-- check other person possible accomplice for anything suspicious

SELECT
  *
FROM
  passengers
  JOIN flights ON flight_id = flights.id
  JOIN airports ON flights.destination_airport_id = airports.id
WHERE
  passengers.passport_number = 3391710505

-- CLUE: 
-- Since nothing has been found on Philip, 
-- And Robin weirdly doesn't have an id in the system
-- The troublemakers are most likely Bruce and Robin
-- 864400  Robin   (375) 555-8161
-- 686048  Bruce  (367) 555-5533  5773159633
-- flight_id  passport_number  seat  id  origin_airport_id  destination_airport_id  year  month  day  hour  minute
-- ---------  ---------------  ----  --  -----------------  ----------------------  ----  -----  ---  ----  ------
-- 36         5773159633       4A    36  8                  4                       2023  7      29   8     20    
-- With the destination being New York City. 
-- .fun times