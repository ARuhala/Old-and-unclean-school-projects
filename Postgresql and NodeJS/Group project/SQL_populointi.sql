INSERT INTO yhteyshenkilo (nimi, email, puhnro,yrityksen_nimi)
		VALUES ('Pekka Pekkala', 'pekka@lol.com', '0443329484','PekanFirma');
		
INSERT INTO yhteyshenkilo (nimi, email, puhnro,yrityksen_nimi)
		VALUES ('Hanna Pekkala', 'hanna@lololol.com', '0445533434','HannanFirma');
		
INSERT INTO yhteyshenkilo (nimi, email, puhnro,yrityksen_nimi)
		VALUES ('Latex', 'latex@email.com', '438943894839','LatexinFirma');
		
		
		
INSERT INTO paikkakunta (nimi)
		VALUES ('Ulvila');
		
INSERT INTO paikkakunta (nimi)
		VALUES ('Tre');
		
INSERT INTO paikkakunta (nimi)
		VALUES ('Hesa');
		
		
		
INSERT INTO postinumero (paikkakunta, postinumero)
		VALUES ((SELECT id FROM paikkakunta WHERE nimi = 'Hesa'), '48838');
		
INSERT INTO postinumero (paikkakunta, postinumero)
		VALUES ((SELECT id FROM paikkakunta WHERE nimi = 'Tre'), '33720');
		
INSERT INTO postinumero (paikkakunta, postinumero)
		VALUES ((SELECT id FROM paikkakunta WHERE nimi = 'Ulvila'), '28720');
		
		
		
INSERT INTO yritysosoite (katuosoite, postinumero)
		VALUES ('Lolkatu 500', (SELECT id FROM postinumero WHERE postinumero = '28720'));
		
INSERT INTO yritysosoite (katuosoite, postinumero)
		VALUES ('Latexkatu 666', (SELECT id FROM postinumero WHERE postinumero = '33720'));
		
INSERT INTO yritysosoite (katuosoite, postinumero)
		VALUES ('Pohinakuja 9000', (SELECT id FROM postinumero WHERE postinumero = '48838'));
		
		

INSERT INTO mainostaja (nimi, ytunnus, yritysosoite_id, yhteyshenkilo_id)
		VALUES ('Pekka Pekkala iso Oyj', '904309433409', (SELECT id FROM yritysosoite WHERE katuosoite = 'Lolkatu 500'),
		(SELECT id FROM yhteyshenkilo WHERE yrityksen_nimi = 'PekanFirma'));
		
INSERT INTO mainostaja (nimi, ytunnus, yritysosoite_id, yhteyshenkilo_id)
		VALUES ('Joona Rehti rahtarit', '90439348', (SELECT id FROM yritysosoite WHERE katuosoite = 'Pohinakuja 9000'),
		(SELECT id FROM yhteyshenkilo WHERE yrityksen_nimi = 'HannanFirma'));
		
INSERT INTO mainostaja (nimi, ytunnus, yritysosoite_id, yhteyshenkilo_id)
		VALUES ('Ruhalan ruutanat', '666999666', (SELECT id FROM yritysosoite WHERE katuosoite = 'Latexkatu 666'),
		(SELECT id FROM yhteyshenkilo WHERE yrityksen_nimi = 'LatexinFirma'));
		

INSERT INTO hinnasto (alkupvm, loppupvm, sekuntihinta)
        VALUES ('2011-11-11', '2020-11-11', 400);
        
INSERT INTO mainosprofiili(sukupuoli, alkuika, loppuika)
        VALUES('mies', 12, 50);
        
INSERT INTO mainosprofiili(sukupuoli, alkuika, loppuika)
        VALUES('nainen', 12, 50);
        
INSERT INTO kayttaja(tunnus, salasana)
        VALUES('tunnus1', 'salasana');
        
INSERT INTO kayttaja(tunnus, salasana)
        VALUES('tunnus2', 'salasana');
        
INSERT INTO henkilokuntakayttaja(rooli, nimi, kayttaja)
        VALUES('Mainosmyyja', 'Pekka Anttinen', (SELECT id FROM kayttaja WHERE tunnus = 'tunnus1'));
        
INSERT INTO henkilokuntakayttaja(rooli, nimi, kayttaja)
        VALUES('taloussihteeri', 'Antti Pekkanen', (SELECT id FROM kayttaja WHERE tunnus = 'tunnus2'));

INSERT INTO Mainoskampanja(nimi, maararaha, jaljella_rahaa, alkupvm, loppupvm, aktiivinen, hinnasto_id, mainostaja_id, mainosprofiili_id, vastuuhlo_id)
        VALUES('Kampanja 1', 20000, 20, '2007-11-11', '2008-11-11', TRUE, (SELECT id FROM hinnasto WHERE alkupvm = '2011-11-11'), (SELECT id FROM mainostaja WHERE ytunnus = '90430943340'),
            (SELECT MAX(id) FROM mainosprofiili), (SELECT MAX(id) FROM henkilokuntakayttaja));
            
INSERT INTO Mainoskampanja(nimi, maararaha, jaljella_rahaa, alkupvm, loppupvm, aktiivinen, hinnasto_id, mainostaja_id, mainosprofiili_id, vastuuhlo_id)
        VALUES('Kampanja 2', 20000, 20, '2008-11-11', '2010-11-11', TRUE, (SELECT id FROM hinnasto WHERE alkupvm = '2011-11-11'), (SELECT id FROM mainostaja WHERE ytunnus = '666999666'),
            (SELECT MIN(id) FROM mainosprofiili), (SELECT MIN(id) FROM henkilokuntakayttaja));
            
INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos11', 2, 'path/path/file', 'default_description', (SELECT MIN(id) FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 1'));
        
INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos12', 2, 'path/path/file', 'default_description', (SELECT MIN(id) FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 1'));

INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos13', 2, 'path/path/file', 'default_description', (SELECT MIN(id) FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 1'));
            
INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos21', 2, 'path/path/file', 'default_description', (SELECT MIN(id)+1 FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 2'));
      
INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos22', 2, 'path/path/file', 'default_description', (SELECT MIN(id)+1 FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 2'));

INSERT INTO Mainos(nimi, kesto, jingle, kuvaus, mainosp_id, mainosk_id)
        VALUES('Mainos23', 2, 'path/path/file', 'default_description', (SELECT MIN(id)+1 FROM mainosprofiili), (SELECT id FROM mainoskampanja WHERE nimi = 'Kampanja 2'));
            
INSERT INTO Lasku
(tilinumero, viitenumero,
 erapaiva, maksettu, summa, karhu, lahetetty, mainoskampanja_id) 
VALUES ('FI49 5000 9420 0287 30', '3309309309',
 TIMESTAMP '2019-08-09', 'false', 64536.03, 'true', 'true', (select id from Mainoskampanja where nimi ='Kampanja 1'));

INSERT INTO Lasku
(tilinumero, viitenumero,
 erapaiva, maksettu, summa, karhu, lahetetty, mainoskampanja_id) 
VALUES ('FI49 5000 9330 0287 30', '22209309',
TIMESTAMP '2019-01-01', 'true', 100432.2, 'true', 'true', (select id from Mainoskampanja where nimi = 'Kampanja 2'));