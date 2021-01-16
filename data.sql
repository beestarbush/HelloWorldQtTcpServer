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
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(0, "40f5206f9f8", "Behang");
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(1, "40f5205fa39", "Vloer");
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(2, "40f52062640", "Stoel");
INSERT INTO ReaderDefinitions(uid, mac_address, description) VALUES(3, "40f52065c93", "Gordijn");

CREATE TABLE CardDefinitions (
	uid INTEGER PRIMARY KEY,
	card_id TEXT NOT NULL,
	description TEXT
);
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(0, "-", "Reserved");
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(1,'909c964a','Tag1');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(2,'e0ee964a','Tag2');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(3,'a0be964a','Tag3');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(4,'c0ab954a','Tag4');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(5,'7082954a','Tag5');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(6,'80a2964a','Tag6');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(7,'7057964a','Tag7');
INSERT INTO CardDefinitions(uid, card_id, description) VALUES(8,'e0f974a','Tag8');

CREATE TABLE FileDefinitions (
	uid INTEGER PRIMARY KEY,
	combination_id INTEGER NOT NULL,
	filename TEXT NOT NULL,
	FOREIGN KEY (combination_id) REFERENCES CombinationMatrix(combination_id)
);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(0, "empty.png");

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
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(0, 2, 0);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(0, 3, 0);

/* 1 - Combination 1 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(1, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(1, "1.png");
/* 2 - Combination 2 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(2, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(2, "2.png");
/* 3 - Combination 3 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(3, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(3, "3.png");
/* 4 - Combination 4 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(4, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(4, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(4, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(4, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(4, "4.png");
/* 5 - Combination 5 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(5, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(5, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(5, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(5, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(5, "5.png");
/* 6 - Combination 6 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(6, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(6, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(6, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(6, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(6, "6.png");
/* 7 - Combination 7 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(7, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(7, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(7, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(7, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(7, "7.png");
/* 8 - Combination 8 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(8, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(8, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(8, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(8, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(8, "8.png");
/* 9 - Combination 9 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(9, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(9, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(9, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(9, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(9, "9.png");
/* 10 - Combination 10 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(10, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(10, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(10, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(10, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(10, "10.png");
/* 11 - Combination 11 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(11, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(11, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(11, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(11, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(11, "11.png");
/* 12 - Combination 12 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(12, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(12, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(12, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(12, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(12, "12.png");
/* 13 - Combination 13 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(13, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(13, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(13, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(13, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(13, "13.png");
/* 14 - Combination 14 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(14, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(14, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(14, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(14, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(14, "14.png");
/* 15 - Combination 15 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(15, 0, 1);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(15, 1, 3);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(15, 2, 5);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(15, 3, 7);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(15, "15.png");
/* 16 - Combination 16 */
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(16, 0, 2);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(16, 1, 4);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(16, 2, 6);
INSERT INTO CombinationMatrix(combination_id, reader_uid, card_uid) VALUES(16, 3, 8);
INSERT INTO FileDefinitions(combination_id, filename) VALUES(16, "16.png");

