
CREATE TABLE ReaderDefinitions (
	uid INTEGER PRIMARY KEY,
	mac_address TEXT NOT NULL,
	description TEXT NOT NULL
);
INSERT INTO ReaderDefinitions(mac_address, description) VALUES("AABBCCDD", "Floor");
INSERT INTO ReaderDefinitions(mac_address, description) VALUES("00112233", "Table");

CREATE TABLE CardDefinitions (
	uid INTEGER PRIMARY KEY,
	card_id TEXT NOT NULL,
	description TEXT
);

CREATE TABLE FileDefinitions (
	uid INTEGER PRIMARY KEY,
	combination_id INTEGER NOT NULL,
	filename TEXT NOT NULL,
	FOREIGN KEY (combination_id) REFERENCES CombinationMatrix(combination_id)
);

CREATE TABLE CombinationMatrix (
	uid INTEGER PRIMARY KEY,
	combination_id INTEGER NOT NULL,
	reader_uid INTEGER NOT NULL,
	card_uid INTEGER NOT NULL,
	FOREIGN KEY (reader_uid) REFERENCES ReaderDefinitions(uid),
	FOREIGN KEY (card_uid) REFERENCES CardDefinitions(uid)
);

