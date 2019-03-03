DROP PROC IF EXISTS uspModifyColumnType
GO

CREATE PROC uspModifyColumnType
	@table VARCHAR(30),
	@column VARCHAR(30),
	@desiredDataType VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + ' ALTER COLUMN ' + QUOTENAME(@column) + ' ' + QUOTENAME(@desiredDataType)

    PRINT @statement
    EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspAddColumn
GO

CREATE PROC uspAddColumn
	@table VARCHAR(30),
	@column VARCHAR(30),
	@desiredDataType VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + ' ADD ' + QUOTENAME(@column) + ' ' + QUOTENAME(@desiredDataType)

    PRINT @statement
    EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspRemoveColumn
GO

CREATE PROC uspRemoveColumn
	@table VARCHAR(30),
	@column VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + ' DROP COLUMN ' + QUOTENAME(@column)

    PRINT @statement
    EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspAddDefaultConstraint
GO

CREATE PROC uspAddDefaultConstraint
	@table VARCHAR(30),
	@constraintName VARCHAR(30),
	@defaultValue VARCHAR(30),	--Should be escaped on call if it is a string
	@column VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + 
						' ADD CONSTRAINT ' + QUOTENAME(@constraintName) +
						' DEFAULT ' + @defaultValue + 
						' FOR ' + QUOTENAME(@column)

    PRINT @statement
    EXECUTE sp_executesql @statement

GO

DROP PROC IF EXISTS uspRemoveDefaultConstraint
GO

CREATE PROC uspRemoveDefaultConstraint
	@table VARCHAR(30),
	@constraintName VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + 
						' DROP CONSTRAINT ' + QUOTENAME(@constraintName)

    PRINT @statement
    EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspRemoveKey
GO

CREATE PROC uspRemoveKey
	@table VARCHAR(30),
	@primaryKeyConstraint VARCHAR(30),
	@column VARCHAR(30)
AS
    DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'ALTER TABLE ' + QUOTENAME(@table) + 
						' DROP CONSTRAINT ' + QUOTENAME(@primaryKeyConstraint) +
						'; ALTER TABLE ' +  QUOTENAME(@table) + 
						' DROP COLUMN ' + QUOTENAME(@column)

    PRINT @statement
    EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspAddPrimaryKey
GO

CREATE PROC uspAddPrimaryKey
	@table VARCHAR(30),
	@primaryKeyConstraint VARCHAR(30),
	@dataType VARCHAR(30),
	@column VARCHAR(30)
AS
    DECLARE @statement1 NVARCHAR(4000)
	DECLARE @statement2 NVARCHAR(4000)
    SELECT @statement1 = 'ALTER TABLE ' + QUOTENAME(@table) + 
						 ' ADD ' + QUOTENAME(@column) + ' ' +
						 QUOTENAME(@dataType) + ' NOT NULL'
	SELECT @statement2 = 'ALTER TABLE ' + QUOTENAME(@table) +
						 ' ADD CONSTRAINT ' + QUOTENAME(@primaryKeyConstraint) +
						 ' PRIMARY KEY (' + @column + ')'

    PRINT @statement1
    EXECUTE sp_executesql @statement1
	PRINT @statement2
	EXECUTE sp_executesql @statement2
GO

DROP PROC IF EXISTS uspAddForeignKey
GO

CREATE PROC uspAddForeignKey
	@table VARCHAR(30),
	@keyConstraint VARCHAR(30),
	@dataType VARCHAR(30),
	@column VARCHAR(30),
	@referenceTable VARCHAR(30),
	@referenceColumn VARCHAR(30)
AS
    DECLARE @statement1 NVARCHAR(4000)
	DECLARE @statement2 NVARCHAR(4000)
    SELECT @statement1 = 'ALTER TABLE ' + QUOTENAME(@table) + 
						 ' ADD ' + QUOTENAME(@column) + ' ' +
						 QUOTENAME(@dataType)
	SELECT @statement2 = 'ALTER TABLE ' + QUOTENAME(@table) +
						 ' ADD CONSTRAINT ' + QUOTENAME(@keyConstraint) +
						 ' FOREIGN KEY (' + @column + ')' +
						 ' REFERENCES ' +  QUOTENAME(@referenceTable) + 
						 '(' + @referenceColumn + ')'

    PRINT @statement1
    EXECUTE sp_executesql @statement1
	PRINT @statement2
	EXECUTE sp_executesql @statement2
GO

DROP PROC IF EXISTS uspAddCandidateKey
GO

CREATE PROC uspAddCandidateKey
	@table VARCHAR(30),
	@column VARCHAR(30),
	@uniqueConstraintName VARCHAR(30),
	@dataType VARCHAR(30)
AS
    DECLARE @statement1 NVARCHAR(4000)
	DECLARE @statement2 NVARCHAR(4000)
    SELECT @statement1 = 'ALTER TABLE ' + QUOTENAME(@table) + 
						 ' ADD ' + QUOTENAME(@column) + ' ' +
						 QUOTENAME(@dataType)
	SELECT @statement2 = 'ALTER TABLE ' + QUOTENAME(@table) +
						 ' ADD CONSTRAINT ' + QUOTENAME(@uniqueConstraintName) +
						 ' UNIQUE (' + @column + ')'

    PRINT @statement1
    EXECUTE sp_executesql @statement1
	PRINT @statement2
	EXECUTE sp_executesql @statement2
GO

DROP PROC IF EXISTS uspCreateTable
GO

CREATE PROC uspCreateTable
	@table VARCHAR(30)
AS
	DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'CREATE TABLE ' + QUOTENAME(@table) + '( id INT )'

	PRINT @statement
	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspDropTable
GO

CREATE PROC uspDropTable
	@table VARCHAR(30)
AS
	DECLARE @statement NVARCHAR(4000)
    SELECT @statement = 'DROP TABLE ' + QUOTENAME(@table)

	PRINT @statement
	EXECUTE sp_executesql @statement
GO

DROP PROC IF EXISTS uspVersion1Do
GO

CREATE PROC uspVersion1Do
AS
	EXEC uspModifyColumnType 'Ingredient', 'price', 'float'
GO

DROP PROC IF EXISTS uspVersion1Undo
GO

CREATE PROC uspVersion1Undo
AS
	EXEC uspModifyColumnType 'Ingredient', 'price', 'int'
GO

DROP PROC IF EXISTS uspVersion2Do
GO

CREATE PROC uspVersion2Do
AS
	EXEC uspAddColumn 'Ingredient', 'price2', 'int'	
GO

DROP PROC IF EXISTS uspVersion2Undo
GO

CREATE PROC uspVersion2Undo
AS
	EXEC uspRemoveColumn 'Ingredient', 'price2'
GO


DROP PROC IF EXISTS uspVersion3Do
GO

CREATE PROC uspVersion3Do
AS
	EXEC uspRemoveDefaultConstraint 'City', 'df_name'
GO

DROP PROC IF EXISTS uspVersion3Undo
GO

CREATE PROC uspVersion3Undo
AS
	EXEC uspAddDefaultConstraint 'City', 'df_name', '''Bucharest''', 'name'
GO

DROP PROC IF EXISTS uspVersion4Do
GO

CREATE PROC uspVersion4Do
AS
	EXEC uspRemoveKey 'Chef', 'PK_Chef', 'cid'
GO

DROP PROC IF EXISTS uspVersion4Undo
GO

CREATE PROC uspVersion4Undo
AS
	EXEC uspAddPrimaryKey 'Chef', 'PK_Chef', 'int', 'cid'
GO

DROP PROC IF EXISTS uspVersion5Do
GO

CREATE PROC uspVersion5Do
AS
	EXEC uspRemoveKey 'Chef', 'FK_Chef_rid', 'rid'
GO

DROP PROC IF EXISTS uspVersion5Undo
GO

CREATE PROC uspVersion5Undo
AS
	EXEC uspAddForeignKey 'Chef', 'FK_Chef_rid', 'int', 'rid', 'Restaurant', 'rid'
GO

DROP PROC IF EXISTS uspVersion6Do
GO

CREATE PROC uspVersion6Do
AS
	EXEC uspAddCandidateKey 'Bed', 'identifier', 'UQ_Bed', 'int'
GO

DROP PROC IF EXISTS uspVersion6Undo
GO

CREATE PROC uspVersion6Undo
AS
	EXEC uspRemoveKey 'Bed', 'UQ_Bed', 'identifier'
GO

DROP PROC IF EXISTS uspVersion7Do
GO

CREATE PROC uspVersion7Do
AS
	EXEC uspCreateTable 'RandomTable'
GO

DROP PROC IF EXISTS uspVersion7Undo
GO

CREATE PROC uspVersion7Undo
AS
	EXEC uspDropTable 'RandomTable'
GO

DROP TABLE IF EXISTS Versions
GO

CREATE TABLE Versions (
	id INT,
	do VARCHAR(30),
	undo VARCHAR(30)
)

INSERT INTO Versions (id, do, undo) VALUES
	(1, 'uspVersion1Do', 'uspVersion1Undo'),
	(2, 'uspVersion2Do', 'uspVersion2Undo'),
	(3, 'uspVersion3Do', 'uspVersion3Undo'),
	(4, 'uspVersion4Do', 'uspVersion4Undo'),
	(5, 'uspVersion5Do', 'uspVersion5Undo'),
	(6, 'uspVersion6Do', 'uspVersion6Undo'),
	(7, 'uspVersion7Do', 'uspVersion7Undo')

DROP TABLE IF EXISTS CurrentVersion
GO

CREATE TABLE CurrentVersion (
	id INT
)

INSERT INTO CurrentVersion (id) VALUES 
	(0)


DROP PROC IF EXISTS uspGoToVersion
GO

CREATE PROC uspGoToVersion
	@version INT
AS
	DECLARE @currentVersion INT
	SELECT @currentVersion = (SELECT * FROM CurrentVersion)

	WHILE @currentVersion > @version
	BEGIN
		DECLARE @functionUndo VARCHAR(30)
		SELECT @functionUndo = (SELECT undo FROM Versions WHERE id = @currentVersion)
		PRINT @functionUndo
		EXEC @functionUndo
		SELECT @currentVersion = @currentVersion - 1
	END

	WHILE @currentVersion < @version
	BEGIN
		SELECT @currentVersion = @currentVersion + 1
		DECLARE @functionDo VARCHAR(30)
		SELECT @functionDo = (SELECT do FROM Versions WHERE id = @currentVersion)
		PRINT @functionDo
		EXEC @functionDo	
	END

	IF (@@ERROR = 0)
		UPDATE CurrentVersion SET id = @currentVersion

		--begin try
		--  raiserror(11
		--end try
		--begin catch
		--
		--end cathc
GO

EXEC uspGoToVersion 0

--get all default constraints, primary keys, foreign keys
select name, type
from sys.objects
where type IN ('D', 'PK', 'F')
order by type