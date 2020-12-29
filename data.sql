CREATE TABLE VersionDefinitions (
	uid INTEGER PRIMARY KEY,
	component TEXT NOT NULL,
	version INTEGER NOT NULL
);
INSERT INTO VersionDefinitions(component, version) VALUES("database", 1);

CREATE TABLE ReaderDefinitions (
	uid INTEGER PRIMARY KEY,
	mac_address TEXT NOT NULL,
	description TEXT NOT NULL
);
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(0, "AABBCCDD", "Floor");
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(1, "00112233", "Table");

CREATE TABLE CardDefinitions (
	uid INTEGER PRIMARY KEY,
	card_id TEXT NOT NULL,
	description TEXT
);
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(0, "-", "Reserved");
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(1, "1020304", "Wood");
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(2, "2020304", "Stone");

CREATE TABLE FileDefinitions (
	uid INTEGER PRIMARY KEY,
	combination_id INTEGER NOT NULL,
	filename TEXT NOT NULL,
	FOREIGN KEY (combination_id) REFERENCES CombinationMatrix(combination_id)
);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(0, "empty.jpg");

CREATE TABLE CombinationMatrix (
	uid INTEGER PRIMARY KEY,
	combination_id INTEGER NOT NULL,
	reader_uid INTEGER NOT NULL,
	card_uid INTEGER NOT NULL,
	FOREIGN KEY (reader_uid) REFERENCES ReaderDefinitions(uid),
	FOREIGN KEY (card_uid) REFERENCES CardDefinitions(uid)
);
/* RESERVED(0) - Empty combination */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(0, 0, 0);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(0, 1, 0);

/* 1 - Combination 1 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 1, 0);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(1, "combination1.jpg");
/* 2 - Combination 2 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 0, 0);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 1, 2);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(2, "combination2.jpg");
/* 3 - Combination 3 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 1, 2);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(3, "combination3.jpg");


