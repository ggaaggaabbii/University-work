INSERT INTO City(latitude, longitude, name)
VALUES (12.3, 45.1, 'Bucharest'),
	   (13.2, 86.4, 'London'),
	   (42.1, 34.5, 'Moscow'),
	   (31.1, 23.1, 'Cluj')

INSERT INTO Hotel(name, address, cid, confort)
VALUES ('Hotel Privo', 'Centrul Vechi', 1, 5),
	   ('Hotel Italia', 'Stefan Cel Mare Nr. 4', 2, 3),
	   ('Hotel Paradis', 'Ion Creanga Nr. 8', 3, 4),
	   ('Pensiunea Vasilica', 'Ion Creanga Nr. 6', 1, 4),
	   ('Hotel Paradis', 'Ion Creanga Nr. 8', 1, 4)

INSERT INTO Employee(name, salary)
VALUES ('Ion', 1300),
	   ('Vasile', 2200),
	   ('Viorel', 2300),
	   ('Alina', 2400),
	   ('Felicia', 2100),
	   ('Laura', 2600)

INSERT INTO Employs(eid, hid)
VALUES (1, 1),
	   (1, 2),
	   (2, 1),
	   (3, 4),
	   (2, 2),
	   (5, 1),
	   (5, 2),
	   (6, 3)

INSERT INTO Restaurant(hid, opening_hour, closing_hour)
VALUES (1, 12, 22),
	   (3, 14, 18),
	   (2, 7, 24),
	   (4, 10, 20)

INSERT INTO Chef (name, stars, rid)
VALUES ('Catalin Scarlatescu', 4, 2),
	   ('Catalin Ghita', 2, 3),
	   ('Florin Dumitrescu', 3, 3),
	   ('Sorin Bontea', 3, 4),
	   ('Henrik Sebok', 5, 1),
	   ('Mung Daal', 4, null)

INSERT INTO Ingredient (name, price, taste)
VALUES ('Sofran', 40, 'sweet'),
	   ('Salt', 10, 'salty'),
	   ('Sugar', 10, 'sweet')

INSERT INTO Recipe(is_vegan, original_country, price)
VALUES (1, 'India', 100),
	   (0, 'Romania', 20),
	   (0, 'Italy', 80),
	   (0, 'France', 65)

INSERT INTO Containing(iid, rid)
VALUES (1, 1),
	   (1, 2),
	   (2, 3),
	   (3, 1)

INSERT INTO Serves(rid, reid)
VALUES (1, 1),
	   (2, 2),
	   (2, 3),
	   (3, 1)

UPDATE Chef
SET stars = stars + 1
WHERE name IS NOT NULL AND stars > 3

UPDATE Chef
SET name = 'Catalin Vasile'
WHERE name LIKE '%Ghita'

UPDATE Employee
SET salary = 2350
WHERE name IN (SELECT name 
			   FROM Employee E
			   WHERE E.salary BETWEEN 2200 AND 2390)

DELETE Employs
WHERE hid IN (SELECT hid
			  FROM Hotel H
			  WHERE H.confort < 4) AND eid IN (SELECT eid
											   FROM Employee
											   WHERE name = 'Ion')

DELETE City
WHERE name = 'Cluj'
