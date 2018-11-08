--Chefs that don't have 3 stars
SELECT C.name
FROM Chef C
WHERE C.stars < 3
UNION ALL
SELECT C2.name
FROM Chef C2
WHERE C2.stars > 3

SELECT C.name
FROM Chef C
WHERE C.stars < 3 OR C.stars > 3

--Hotels that are in Moscow or in Bucharest
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest')
UNION ALL
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Moscow')

SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest' OR C.name = 'Moscow')

--Hotels that have representatives both in Moscow and Bucharest
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest')
INTERSECT
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Moscow')

SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest') AND H.name IN (SELECT H.name
														   FROM Hotel H
														   WHERE H.cid IN (SELECT C.cid
																		   FROM City C
																		   WHERE C.name = 'Moscow'))

--Employees that work for both Hotel Italia and Hotel Privo
SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Privo'
INTERSECT
SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Italia'

SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E.eid = E2.eid AND E2.hid = H.hid AND H.name LIKE '% Privo' AND E.name IN (SELECT E.name
																				 FROM Employee E, Employs E2, Hotel H
																				 WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Italia')

--Hotels that have representatives both in Bucharest but not in Moscow
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest')
EXCEPT
SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Moscow')

SELECT H.name
FROM Hotel H
WHERE H.cid IN (SELECT C.cid
				FROM City C
				WHERE C.name = 'Bucharest') AND H.name NOT IN (SELECT H.name
															   FROM Hotel H
															   WHERE H.cid IN (SELECT C.cid
																			   FROM City C
																		       WHERE C.name = 'Moscow'))

--Employees that work for both Hotel Privo but not in Hotel Italia
SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Privo'
EXCEPT
SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Italia'

SELECT E.name
FROM Employee E, Employs E2, Hotel H
WHERE E.eid = E2.eid AND E2.hid = H.hid AND H.name LIKE '% Privo' AND E.name NOT IN (SELECT E.name
																					 FROM Employee E, Employs E2, Hotel H
																					 WHERE E2.eid = E.eid AND E2.hid = H.hid AND H.name LIKE '% Italia')
--Joins
SELECT *
FROM Employee E INNER JOIN Employs E2 ON E.eid = E2.eid
INNER JOIN Hotel H ON E2.hid = H.hid

SELECT *
FROM Employee E LEFT JOIN Employs E2 ON E.eid = E2.eid
LEFT JOIN Hotel H ON E2.hid = H.hid

SELECT *
FROM Employee E RIGHT JOIN Employs E2 ON E.eid = E2.eid
RIGHT JOIN Hotel H ON E2.hid = H.hid

SELECT *
FROM Employee E FULL JOIN Employs E2 ON E.eid = E2.eid
FULL JOIN Hotel H ON E2.hid = H.hid

--Hotels that have Restaurants that serve sweet recipes
SELECT DISTINCT H.name
FROM Restaurant R FULL JOIN Serves S ON S.reid = R.rid
FULL JOIN Recipe Re ON Re.rid = S.rid
FULL JOIN Containing C ON Re.rid = C.rid
FULL JOIN Ingredient I ON C.iid = I.iid
RIGHT JOIN Hotel H ON R.hid = H.hid
WHERE I.taste LIKE '%sweet%'

--Chefs and the Cities the work in
SELECT C.name, Ci.name
FROM Chef C FULL JOIN Restaurant R ON C.rid = R.rid
FULL JOIN Hotel H ON R.hid = H.hid
FULL JOIN City Ci ON Ci.cid = H.cid

--For each employee show the hotel they work in
SELECT E.name, H.name
FROM Employee E INNER JOIN Employs Em ON Em.eid = E.eid
INNER JOIN Hotel H on Em.hid = H.hid

--For each employee show the city they work in
SELECT E.name, C.name
FROM Employee E INNER JOIN Employs Em ON Em.eid = E.eid
INNER JOIN Hotel H on Em.hid = H.hid
INNER JOIN City C ON H.cid = C.cid


--Recipes that contain sweet Ingredients
SELECT R.is_vegan, R.original_country, R.price
FROM Recipe R
WHERE R.rid IN (SELECT C.rid
				FROM Containing C
				WHERE C.iid IN (SELECT I.iid
								FROM Ingredient I
								WHERE I.taste LIKE '%sweet%'))
ORDER BY R.price

SELECT DISTINCT R.is_vegan, R.original_country, R.price
FROM Recipe R, Containing C
WHERE R.rid = C.rid AND C.iid IN (SELECT I.iid
								  FROM Ingredient I
								  WHERE I.taste LIKE '%sweet%' AND I.iid = C.iid)
ORDER BY R.price

--Most expensive Recipe that contains sweet Ingredients
SELECT TOP 1 R.is_vegan, R.original_country, R.price
FROM Recipe R, Containing C
WHERE R.rid = C.rid AND C.iid IN (SELECT I.iid
								  FROM Ingredient I
								  WHERE I.taste LIKE '%sweet%' AND I.iid = C.iid)
ORDER BY R.price DESC

--Ingredients that are included in a recipe
SELECT I.name
FROM Ingredient I
WHERE EXISTS (SELECT *
			  FROM Recipe R, Containing C
			  WHERE R.rid = C.rid AND C.iid = I.iid)

--Unemployed Chefs
SELECT C.name
FROM Chef C
WHERE NOT EXISTS (SELECT *
				  FROM Restaurant R
				  WHERE R.rid = C.rid)

--Chefs that work in Bucharest
SELECT C1.name, C1.city
FROM (SELECT C.name AS name, Ci.name AS city
	  FROM Chef C LEFT JOIN Restaurant R ON C.rid = R.rid
	  LEFT JOIN Hotel H ON R.hid = H.hid
	  LEFT JOIN City Ci ON Ci.cid = H.cid) AS C1
WHERE C1.city = 'Bucharest'

--Employees that work in multiple hotels and can come in contact 
--with Henrik Sebok (work in the same hotel), 
--but are not named Vasile
SELECT DISTINCT E.name, E.hotel
FROM (SELECT E1.name AS name, E1.hotel
	  FROM (SELECT H.hid AS hid, H.name AS hotel, E2.name AS name
			FROM Hotel H
			INNER JOIN Employs Ep ON H.hid = Ep.hid
			INNER JOIN Employee E2 ON E2.eid = Ep.eid
			WHERE EXISTS (SELECT *
						  FROM Chef C, Restaurant R
						  WHERE C.rid = R.rid AND R.hid = H.hid AND C.name = 'Henrik Sebok')
			) AS E1
	  ) AS E
WHERE E.name NOT LIKE '%Vasile%' AND E.name IN (SELECT E3.name
												FROM Employee E3
												WHERE EXISTS (SELECT Emp.eid, COUNT(*) as Co
															  FROM Employs Emp
														      WHERE E3.eid = Emp.eid
															  GROUP BY Emp.eid
															  HAVING 2 <= COUNT(*)
															))
	  
--Chefs grouped by stars in descending order
SELECT C.name, C.stars
FROM Chef C
GROUP BY C.stars, C.name
ORDER BY C.stars DESC

--Chefs with 3 stars grouped by name
SELECT C.name, C.stars
FROM Chef C
GROUP BY C.name, C.stars
HAVING C.stars = 3

--Employees working at at least 2 hotels
SELECT E.eid, E.name
FROM Employee E
GROUP BY E.eid, E.name
HAVING 2 <= (SELECT COUNT(*)
			 FROM Employs Emp
		     WHERE E.eid = Emp.eid)

--Employees having a salary above the average
SELECT E.eid, E.name, E.salary
FROM Employee E
GROUP BY E.eid, E.name, E.salary
HAVING E.salary > (SELECT AVG(E2.salary)
				   FROM Employee E2)

--Employees with a salary bigger than any employee named Ion
SELECT DISTINCT E.name
FROM Employee E
WHERE E.salary > ANY (SELECT E2.salary
					  FROM Employee E2
					  WHERE E2.name LIKE '%Ion%')

--Employees with the lowest salary
SELECT DISTINCT E.name, E.salary
FROM Employee E
WHERE E.salary <= ALL (SELECT E2.salary
					   FROM Employee E2)

SELECT DISTINCT E.name, E.salary
FROM Employee E
GROUP BY E.name, E.salary
HAVING E.salary = (SELECT MIN(E2.salary)
				   FROM Employee E2)

--Top 3 Chefs with the highest number of stars
SELECT DISTINCT TOP 3 C.name, C.stars
FROM Chef C
WHERE C.stars >= ALL (SELECT C2.stars
					  FROM Chef C2)

SELECT DISTINCT TOP 3 C.name, C.stars
FROM Chef C
GROUP BY C.name, C.stars
HAVING C.stars = (SELECT MAX(C2.stars)
				  FROM Chef C2)

--Hotels with more employees than a Hotel Paradis
SELECT H.hid, H.name
FROM Hotel H
WHERE dbo.ufnGetNumberOfEmployees(hid) > ANY(SELECT dbo.ufnGetNumberOfEmployees(hid) as number
											 FROM Hotel H
											 WHERE H.name LIKE '%Paradis%')

--maximum salary for each hotel
SELECT H.name, MAX(E.salary)
FROM Employee E, Hotel H, Employs Em
WHERE E.eid = Em.eid AND Em.hid = H.hid
GROUP BY H.name

--maximum salary for each hotel that has a minimum of 2 emplyees
--subquery is not necesary
SELECT H.name, MAX(E.salary)
FROM Employee E, Hotel H, Employs Em
WHERE E.eid = Em.eid AND Em.hid = H.hid
GROUP BY H.name
HAVING 2 <= (SELECT COUNT(*)
			 FROM Employee E2, Hotel H2, Employs Em2
			 WHERE E2.eid = Em2.eid AND Em2.hid = H2.hid AND H.name = H2.name)

--countries and the number of ingredients used for recipes if they have more than 2
SELECT R.original_country, COUNT(*)
FROM Ingredient I, Recipe R
GROUP BY R.original_country
HAVING COUNT(*) > 2

--Countries and the number of ingredients used for recipes if they have more than 2 sweet ingredients
--subquery is necesary
SELECT R.original_country, COUNT(*)
FROM Ingredient I INNER JOIN Containing C ON C.iid = I.iid
INNER JOIN Recipe R ON R.rid = C.rid
GROUP BY R.original_country
HAVING 2 <= (SELECT COUNT(*)
			 FROM Ingredient I2
			 INNER JOIN Containing C ON C.iid = I2.iid
			 INNER JOIN Recipe R2 ON C.rid = R2.rid 
			 WHERE I2.taste LIKE '%sweet%' AND R2.original_country = R.original_country)