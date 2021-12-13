-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Chamberlin Street";
id | year | month | day | street | description
295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
-- shows the report of the theft

SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Chamberlin Street";
id | year | month | day | street | description
295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
sqlite> SELECT * FROM interviews WHERE day = 28 AND month = 7;
id | name | year | month | day | transcript
160 | Barbara | 2020 | 7 | 28 | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--see the transcripts from the day

SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = "exit";
id | year | month | day | hour | minute | activity | license_plate
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55
-- see which cars exited the courthouse within 10 mins of 10.15

SELECT name, license_plate FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = "exit");
name | license_plate
Patrick | 5P2BI95
Amber | 6P58WS2
Elizabeth | L93JTIZ
Roger | G412CB7
Danielle | 4328GD8
Russell | 322W7JE
Evelyn | 0NTHK55
Ernest | 94KL13X

SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
id | account_number | year | month | day | atm_location | transaction_type | amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35
-- see which accounts were withdrawn from at Fifer St on the day

SELECT name, account_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
name | account_number
Ernest | 49610011
Russell | 26013199
Roy | 16153065
Bobby | 28296815
Elizabeth | 25506511
Danielle | 28500762
Madison | 76054385
Victoria | 81061156
-- see who withdrew money & their account number of those who withdrew money from Fifer St

SELECT caller, receiver FROM phone_calls WHERE month = 7 AND day = 28;
caller | receiver
(336) 555-0077 | (098) 555-1164
(918) 555-5327 | (060) 555-2489
(491) 555-2505 | (478) 555-1565
(996) 555-8899 | (059) 555-4698
(704) 555-5790 | (772) 555-5770
(984) 555-5921 | (618) 555-9856
(579) 555-5030 | (971) 555-6468
(233) 555-0473 | (831) 555-0973
(293) 555-1469 | (749) 555-4874
(450) 555-8297 | (771) 555-7880
(130) 555-0289 | (996) 555-8899
(209) 555-7806 | (693) 555-7986
(918) 555-2946 | (006) 555-0505
(499) 555-9472 | (892) 555-8872
(669) 555-6918 | (914) 555-5994
(547) 555-8781 | (398) 555-1013
(544) 555-8087 | (389) 555-5198
(666) 555-5774 | (125) 555-8030
(047) 555-0577 | (059) 555-4698
(301) 555-4174 | (711) 555-3007
(801) 555-9266 | (984) 555-5921
(971) 555-6468 | (267) 555-2761
(367) 555-5533 | (375) 555-8161
(609) 555-5876 | (389) 555-5198
(357) 555-0246 | (502) 555-6712
(367) 555-5533 | (344) 555-9601
(394) 555-3247 | (035) 555-2997
(839) 555-1757 | (487) 555-5865
(770) 555-1196 | (324) 555-0416
(636) 555-4198 | (670) 555-8598
(068) 555-0183 | (770) 555-1861
(711) 555-3007 | (113) 555-7544
(060) 555-2489 | (204) 555-4136
(704) 555-2131 | (891) 555-5672
(367) 555-5533 | (022) 555-4052
(873) 555-3868 | (047) 555-0577
(867) 555-9103 | (068) 555-0183
(608) 555-9302 | (725) 555-3243
(901) 555-8732 | (491) 555-2505
(478) 555-1565 | (717) 555-1342
(499) 555-9472 | (717) 555-1342
(695) 555-0348 | (338) 555-6650
(696) 555-9195 | (258) 555-5627
(286) 555-6063 | (676) 555-6554
(770) 555-1861 | (725) 555-3243
(711) 555-3007 | (147) 555-6818
(725) 555-4692 | (821) 555-5262
(324) 555-0416 | (452) 555-8550
(234) 555-1294 | (772) 555-5770
(669) 555-6918 | (971) 555-6468
(031) 555-6622 | (910) 555-3251
(342) 555-9260 | (219) 555-0139
(342) 555-9260 | (487) 555-5865
(801) 555-9266 | (608) 555-9302
(398) 555-1013 | (329) 555-5870
(016) 555-9166 | (336) 555-0077
(594) 555-2863 | (491) 555-2505
(122) 555-4581 | (831) 555-0973
(914) 555-5994 | (973) 555-3809
(258) 555-5627 | (695) 555-0348
(751) 555-6567 | (594) 555-6254
(771) 555-7880 | (711) 555-3007
(219) 555-0139 | (867) 555-9103
(676) 555-6554 | (328) 555-9658
(749) 555-4874 | (492) 555-5484
(328) 555-9658 | (775) 555-7584
(219) 555-0139 | (910) 555-3251
(380) 555-4380 | (680) 555-4935
(826) 555-1652 | (066) 555-9701
(594) 555-6254 | (123) 555-5144
(338) 555-6650 | (704) 555-2131
(971) 555-6468 | (258) 555-5627
(730) 555-5115 | (343) 555-0167
(286) 555-6063 | (310) 555-8568
(367) 555-5533 | (704) 555-5790
(041) 555-4011 | (609) 555-5876
(478) 555-1565 | (031) 555-6622
-- see the callers & receivers on this day (cross ref to tables below)

SELECT name, phone_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28);
name | phone_number
Jordan | (328) 555-9658
Patrick | (725) 555-4692
Sean | (867) 555-9103
Margaret | (068) 555-0183
Louis | (749) 555-4874
Amber | (301) 555-4174
James | (676) 555-6554
Diana | (918) 555-2946
Virginia | (478) 555-1565
Christina | (547) 555-8781
Cheryl | (450) 555-8297
Eugene | (666) 555-5774
Ryan | (901) 555-8732
Judy | (918) 555-5327
Joan | (711) 555-3007
Christine | (608) 555-9302
Walter | (544) 555-8087
Carolyn | (234) 555-1294
Alexander | (801) 555-9266
Bobby | (826) 555-1652
Roger | (130) 555-0289
Teresa | (041) 555-4011
Victoria | (338) 555-6650
Madison | (286) 555-6063
Roy | (122) 555-4581
Billy | (060) 555-2489
Anna | (704) 555-2131
Jean | (695) 555-0348
Zachary | (839) 555-1757
Russell | (770) 555-1861
Randy | (984) 555-5921
Olivia | (258) 555-5627
William | (324) 555-0416
Evelyn | (499) 555-9472
Kathryn | (609) 555-5876
Jack | (996) 555-8899
Paul | (357) 555-0246
Betty | (233) 555-0473
Arthur | (394) 555-3247
Dylan | (380) 555-4380
Bryan | (696) 555-9195
Ralph | (771) 555-7880
Peter | (751) 555-6567
Rose | (336) 555-0077
Carl | (704) 555-5790
Brittany | (398) 555-1013
John | (016) 555-9166
Ethan | (594) 555-6254
Ernest | (367) 555-5533
Terry | (730) 555-5115
Jason | (636) 555-4198
Ashley | (770) 555-1196
Dorothy | (047) 555-0577
Daniel | (971) 555-6468
Nathan | (293) 555-1469
Douglas | (491) 555-2505
Keith | (209) 555-7806
Harold | (669) 555-6918
Jose | (914) 555-5994
Patricia | (594) 555-2863
Beverly | (342) 555-9260
Andrew | (579) 555-5030
Mark | (873) 555-3868
Kimberly | (031) 555-6622
Logan | (219) 555-0139
-- see everyone who called on this day

SELECT name, phone_number FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28);
name | phone_number
Pamela | (113) 555-7544
Jordan | (328) 555-9658
Heather | (502) 555-6712
Sean | (867) 555-9103
Margaret | (068) 555-0183
Louis | (749) 555-4874
James | (676) 555-6554
Larry | (892) 555-8872
Virginia | (478) 555-1565
Gregory | (022) 555-4052
Brenda | (831) 555-0973
Joan | (711) 555-3007
Christine | (608) 555-9302
Rebecca | (891) 555-5672
Christopher | (775) 555-7584
Kayla | (487) 555-5865
Joshua | (267) 555-2761
Ruth | (772) 555-5770
Victoria | (338) 555-6650
Danielle | (389) 555-5198
Billy | (060) 555-2489
Anna | (704) 555-2131
Jesse | (693) 555-7986
Stephanie | (204) 555-4136
Jean | (695) 555-0348
Russell | (770) 555-1861
Randy | (984) 555-5921
Olivia | (258) 555-5627
William | (324) 555-0416
Kathryn | (609) 555-5876
Jack | (996) 555-8899
Ralph | (771) 555-7880
Benjamin | (680) 555-4935
Joe | (452) 555-8550
Melissa | (717) 555-1342
Amanda | (821) 555-5262
Rose | (336) 555-0077
Carl | (704) 555-5790
Brittany | (398) 555-1013
Ethan | (594) 555-6254
Rachel | (006) 555-0505
Jacqueline | (910) 555-3251
Dorothy | (047) 555-0577
Maria | (492) 555-5484
Sharon | (343) 555-0167
Daniel | (971) 555-6468
Douglas | (491) 555-2505
Kyle | (035) 555-2997
Diane | (147) 555-6818
Nicole | (123) 555-5144
Gloria | (973) 555-3809
Frances | (059) 555-4698
Kevin | (618) 555-9856
Jose | (914) 555-5994
Emma | (329) 555-5870
Philip | (725) 555-3243
Berthold | (375) 555-8161
Kimberly | (031) 555-6622
Raymond | (125) 555-8030
Robert | (098) 555-1164
Amy | (670) 555-8598
Doris | (066) 555-9701
Logan | (219) 555-0139
Deborah | (344) 555-9601
Angela | (310) 555-8568
-- see everyone who received a call on this day

SELECT name FROM people WHERE name IN 
(SELECT name FROM people WHERE id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN 
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))) 
AND name IN 
(SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28));
name
Bobby
Victoria
Madison
Roy
Russell
Ernest
-- see who withdrew money AND called on the same day

SELECT name FROM people WHERE name IN 
(SELECT name FROM people WHERE id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN 
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))) 
AND name IN 
(SELECT name FROM people WHERE phone_number IN 
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28)) 
AND name IN 
(SELECT name FROM people WHERE license_plate IN 
(SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = "exit"));
name
Madison
Russell
Ernest
--The list of people who drew money, made a phone call AND left the parking between 10am-11am
--remove Madison as she left after 10.25am, more than 10 mins after 10.15am.

SELECT * FROM flights WHERE day = 29 AND month = 7 ORDER BY hour, minute;
id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30
23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15
53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20
18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0
--sees all the flights the next day sorted by hours and minutes

SELECT * FROM airports WHERE id = 4;
id | abbreviation | full_name | city
4 | LHR | Heathrow Airport | London
--sees the destination airport for the earliest flight
--Our thief must have escaped to London

SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 ORDER BY hour, minute LIMIT 1);
flight_id | passport_number | seat
36 | 7214083635 | 2A
36 | 1695452385 | 3B
36 | 5773159633 | 4A
36 | 1540955065 | 5C
36 | 8294398571 | 6C
36 | 1988161715 | 6D
36 | 9878712108 | 7A
36 | 8496433585 | 7B
--sees all the passengers on the earliest flight

SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
name
Bobby
Roger
Madison
Danielle
Evelyn
Edward
Ernest
Doris
--got a bit lazy & hardcoded 36: find the names of all the passengers on the earliest flight
--from visually checking, the thief MUST be Ernest!

SELECT name FROM people 
WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = "Ernest") AND day = 28 AND month = 7);
name
Gregory
Carl
Berthold
Deborah
--see the names of those who Ernest called on 28 July

SELECT * FROM people WHERE name = "Gregory" OR name = "Carl" OR name = "Berthold" OR name = "Deborah";
id | name | phone_number | passport_number | license_plate
315221 | Gregory | (022) 555-4052 | 3355598951 | V4C670D
652398 | Carl | (704) 555-5790 | 7771405611 | 81MZ921
864400 | Berthold | (375) 555-8161 |  | 4V16VO0
985497 | Deborah | (344) 555-9601 | 8714200946 | 10I5658
--see the data of the last 4 suspects
--Berthold has no passport number - it could be him?