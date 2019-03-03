DROP FUNCTION IF EXISTS dbo.GetColumns
GO

CREATE FUNCTION dbo.GetColumns (@tableName VARCHAR(30))
RETURNS TABLE
AS
RETURN
(
	SELECT C.name, T.name As Type
	FROM sys.columns C INNER JOIN sys.types T ON C.system_type_id = T.system_type_id
	WHERE C.object_id = OBJECT_ID(@tableName)
)
GO

DROP PROC IF EXISTS uspInsertARandomValueForNoFkTable
GO

CREATE PROC uspInsertARandomValueForNoFkTable
	@tableName VARCHAR(30)
AS
	DECLARE @Colmns TABLE(name VARCHAR(30), type VARCHAR(30))
	DECLARE @insertStmt NVARCHAR(2000)
	DECLARE @insertValues NVARCHAR(2000)
	DECLARE @colName VARCHAR(30)
	DECLARE @colType VARCHAR(30)
	DECLARE @statement NVARCHAR(4000)

	INSERT INTO @Colmns
	SELECT * FROM dbo.GetColumns(@tableName)

	SELECT @insertStmt = N'INSERT INTO ' + QUOTENAME(@tableName) + ' ('
	SELECT @insertValues = N'VALUES('

	-- declare a cursor on the columns
	DECLARE colCursor CURSOR
		FOR SELECT * FROM @Colmns

	OPEN colCursor

	FETCH NEXT FROM colCursor
	INTO @colName, @colType

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @insertStmt = @insertStmt + @colName

		IF @colType = 'int'
			SELECT @insertValues = @insertValues + CONVERT(NVARCHAR(255), ABS(CHECKSUM(NEWID())))
		ELSE IF @colType = 'varchar'
			SELECT @insertValues = @insertValues + N'CONVERT(varchar(255), NEWID())'
		ELSE IF @colType = 'float'
			SELECT @insertValues = @insertValues + CONVERT(NVARCHAR(255), ABS(CHECKSUM(NEWID())))
		ELSE IF @colType = 'char'
			SELECT @insertValues = @insertValues + N'CONVERT(varchar(255), NEWID())'
		
		FETCH NEXT FROM colCursor
		INTO @colName, @colType

		IF @@FETCH_STATUS = 0
		BEGIN
			SELECT @insertStmt = @insertStmt + N','
			SELECT @insertValues = @insertValues + N','
		END

	END

	SELECT @insertStmt = @insertStmt + N') '
	SELECT @insertValues = @insertValues + N')'

	SELECT @statement = @insertStmt + @insertValues
	PRINT @statement

	EXECUTE sp_executesql @statement

	-- create a string with 'INSERT INTO' + '@values from the name column' + (@values from the type)
GO


EXEC uspInsertARandomValueForNoFkTable 'Ingredient'

--SELECT * FROM dbo.GetColumns('Chef')
--SELECT CONVERT(varchar(255), NEWID()); -- random string generator