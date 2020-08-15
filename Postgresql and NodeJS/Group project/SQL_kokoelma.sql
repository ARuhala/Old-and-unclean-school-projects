CREATE TYPE sukupuolienum AS ENUM ('mies', 'nainen', 'muu');
CREATE TYPE roolienum AS ENUM('taloussihteeri', 'Mainosmyyja');

CREATE TABLE Genre (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(100) NOT NULL
);


CREATE TABLE Kappale (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(255) NOT NULL
);


CREATE TABLE Esittaja (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(255) NOT NULL
);


CREATE TABLE Maa (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(100) NOT NULL
);


CREATE TABLE Paikkakunta(
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(100) NOT NULL
);


CREATE TABLE Hinnasto(
	id SERIAL  PRIMARY KEY,
	alkupvm DATE NOT NULL,
	loppupvm DATE NOT NULL,
	sekuntihinta INTEGER NOT NULL CHECK (sekuntihinta BETWEEN 0 AND 9999)
);
	
CREATE TABLE Yhteyshenkilo(
	id SERIAL PRIMARY KEY,
	nimi VARCHAR(100) NOT NULL,
	email VARCHAR(100)NOT NULL,
	puhnro VARCHAR(30)NOT NULL,
	yrityksen_nimi VARCHAR(100) NOT NULL
);

CREATE TABLE Asiakas(
	id SERIAL PRIMARY KEY,
	ika INT check (ika >= 0),
	sukupuoli sukupuolienum NOT NULL,
	paikkakunta  INTEGER REFERENCES Paikkakunta(id) ON DELETE SET NULL
);



CREATE TABLE Kayttaja(
	id SERIAL PRIMARY KEY,
	tunnus VARCHAR(12),
	salasana VARCHAR(255) 
);

CREATE TABLE Asiakaskayttaja(
	id SERIAL PRIMARY KEY,
	asiakas INTEGER REFERENCES Asiakas(id) ON DELETE CASCADE,
	kayttaja INTEGER REFERENCES Kayttaja(id) ON DELETE CASCADE
);





CREATE TABLE Henkilokuntakayttaja(
	id SERIAL PRIMARY KEY,
	rooli roolienum,
	nimi VARCHAR(100) NOT NULL,
	kayttaja INTEGER REFERENCES Kayttaja(id) ON DELETE CASCADE
);
CREATE TABLE Postinumero(
	id SERIAL PRIMARY KEY,
	postinumero VARCHAR(100),
	paikkakunta INTEGER REFERENCES Paikkakunta(id) ON DELETE SET NULL
);

CREATE TABLE yritysosoite (
  id SERIAL NOT NULL PRIMARY KEY,
  katuosoite VARCHAR(100) NOT NULL,
  postinumero INTEGER REFERENCES postinumero(id) ON DELETE SET NULL
);


CREATE TABLE Mainosprofiili(
	id SERIAL PRIMARY KEY,
	sukupuoli sukupuolienum NOT NULL,
	alkuika INTEGER NOT NULL CHECK (alkuika > 0),
	loppuika INTEGER NOT NULL CHECK (loppuika > 0)
);

CREATE TABLE Mainostaja (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(100) NOT NULL,
  ytunnus VARCHAR(100) NOT NULL,
  yritysosoite_id INTEGER NOT NULL REFERENCES yritysosoite(id) ON DELETE RESTRICT,
  yhteyshenkilo_id INTEGER REFERENCES yhteyshenkilo(id) ON DELETE SET NULL
);


CREATE TABLE Mainoskampanja (
	id SERIAL PRIMARY KEY,
	nimi VARCHAR(100) NOT NULL,
	maararaha INTEGER NOT NULL CHECK (maararaha BETWEEN 0 AND 9999999999),
	jaljella_rahaa INTEGER NOT NULL CHECK (jaljella_rahaa BETWEEN 0 AND 9999999999),
	alkupvm DATE NOT NULL,
	loppupvm DATE NOT NULL,
	aktiivinen BOOLEAN NOT NULL,
	hinnasto_id INTEGER REFERENCES Hinnasto(id) ON UPDATE RESTRICT ON DELETE RESTRICT ,
	mainostaja_id INTEGER REFERENCES Mainostaja(id) ON DELETE RESTRICT,
	mainosprofiili_id INTEGER REFERENCES Mainosprofiili(id) ON DELETE SET NULL,
	vastuuhlo_id INTEGER REFERENCES Henkilokuntakayttaja(id) ON DELETE RESTRICT
	);
	
CREATE TABLE Mainos (
  id SERIAL NOT NULL PRIMARY KEY,
  nimi VARCHAR(100) NOT NULL,
  kesto INTEGER NOT NULL CHECK (kesto BETWEEN 1 AND 9999),
  jingle VARCHAR(255) NOT NULL,
  kuvaus VARCHAR(255) NOT NULL,
  mainosp_id INTEGER REFERENCES mainosprofiili(id) ON DELETE SET NULL,
  mainosk_id INTEGER NOT NULL REFERENCES mainoskampanja(id) ON DELETE CASCADE
);
  
  
CREATE TABLE Mainosnaytto (
  id SERIAL NOT NULL PRIMARY KEY,
  kesto INTEGER NOT NULL CHECK (kesto BETWEEN 1 AND 9999),
  timestamp TIMESTAMP,
  mainos_id INTEGER NOT NULL REFERENCES mainos(id) ON DELETE RESTRICT,
  asiakas_id INTEGER REFERENCES asiakas(id) ON DELETE SET NULL
);
	


CREATE TABLE Lasku(
	id SERIAL PRIMARY KEY,
	tilinumero VARCHAR(33) NOT NULL,
	viitenumero TEXT NOT NULL CHECK (char_length(viitenumero) >= 7 AND char_length(viitenumero) <=20) ,
	erapaiva TIMESTAMP NOT NULL,
	maksettu BOOLEAN NOT NULL,
	summa FLOAT NOT NULL,
	karhu BOOLEAN NOT NULL,
	lahetetty BOOLEAN NOT NULL,
	mainoskampanja_id INTEGER REFERENCES Mainoskampanja(id) ON DELETE SET NULL
);

CREATE TABLE Lahetysaika(
	id SERIAL PRIMARY KEY,
	alkuklo TIME NOT NULL,
	loppuklo TIME NOT NULL,
	mainosprofiili_id INTEGER REFERENCES Mainosprofiili(id) ON DELETE CASCADE
);


	
CREATE TABLE Mainosp_genre(
	mainospid INTEGER REFERENCES Mainosprofiili(id) ON UPDATE CASCADE ON DELETE CASCADE,
	genreid INTEGER REFERENCES Genre(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Mainosp_kappale(
	mainospid INTEGER REFERENCES Mainosprofiili(id) ON UPDATE CASCADE ON DELETE CASCADE,
	kappaleid INTEGER REFERENCES Kappale(id)  ON UPDATE CASCADE ON DELETE CASCADE
);
	
CREATE TABLE Mainosp_esittaja(
	mainospid INTEGER REFERENCES Mainosprofiili(id) ON UPDATE CASCADE ON DELETE CASCADE,
	esittajaid INTEGER REFERENCES Esittaja(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Mainosp_maa(
	mainospid INTEGER REFERENCES Mainosprofiili(id) ON UPDATE CASCADE ON DELETE CASCADE,
	maaid INTEGER REFERENCES Maa(id) ON UPDATE CASCADE ON DELETE CASCADE
);
	
CREATE TABLE Mainosp_paikkakunta(
	mainospid INTEGER REFERENCES Mainosprofiili(id) ON UPDATE CASCADE ON DELETE CASCADE,
	paikkakid INTEGER REFERENCES Paikkakunta(id) ON UPDATE CASCADE ON DELETE CASCADE
);
	
-- Alunperin postinumero-relaatiosta puuttui itse postinumero, joka huomattua sinne lisättiin
-- juurikaan muita ongelmia ei ollut. Teimme myös sellaisen muutoksen, että kunkin relaation id:t
-- muutettiin muotoon id, muodosta "relaationnimiid", mikä helpotti huomattavasti elämäämme.
-- Laitoimme rajoitteet create table -komentojen yhteyteen, emme käyttäneet alter table add constrain -komentoja







