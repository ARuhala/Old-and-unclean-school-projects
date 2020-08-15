CREATE VIEW Taloussihteeri AS

	lasku.id AS lasku_id, tilinumero, viitenumero, erapaiva, maksettu, summa, karhu, lahetetty, lasku.mainoskampanja_id AS lasku_mainoskampanja_id,
	
	mainoskampanja.id AS mainoskampanja_id, mainoskampanja.nimi AS mainoskampanja_nimi, maararaha, jaljella_rahaa, mainoskampanja.alkupvm AS mainoskampanja_alkupvm,
	mainoskampanja.loppupvm AS mainoskampanja_loppupvm, aktiivinen, mainoskampanja.hinnasto_id AS mainoskampanja_hinnasto_id, 
	mainoskampanja.mainostaja_id AS mainoskampanja_mainostaja_id, mainosprofiili_id, vastuuhlo_id,
	
	hinnasto.id AS hinnasto_id, hinnasto.alkupvm AS hinnasto_alkupvm, hinnasto.loppupvm AS hinnasto_loppupvm,sekuntihinta,
	
	mainostaja.id AS mainostaja_id, mainostaja.nimi AS mainostaja_nimi, ytunnus, mainostaja.yritysosoite_id AS mainostaja_yritysosoite_id, 
	mainostaja.yhteyshenkilo_id AS mainostaja_yhteyshenkilo_id,
	
	yritysosoite.id AS yritysosoite_id, katuosoite, yritysosoite.postinumero AS yritysosoite_postinumero,
	
	postinumero.id AS postinumero_id, paikkakunta, postinumero.postinumero,
	
	paikkakunta.id AS paikkakunta_id, paikkakunta.nimi AS paikkakunta_nimi,
	
	yhteyshenkilo.id AS yhteyshenkilo_id, yhteyshenkilo.nimi AS yhteyshenkilo_nimi, email, puhnro, yrityksen_nimi
	
	FROM lasku, mainoskampanja, hinnasto, mainostaja,
		yritysosoite, postinumero, paikkakunta, yhteyshenkilo
		
	WHERE lasku.mainoskampanja_id = mainoskampanja.id
		AND hinnasto.id = mainoskampanja.hinnasto_id
		AND mainoskampanja.mainostaja_id = mainostaja.id
		AND yritysosoite.id = mainostaja.yritysosoite_id
		AND postinumero.id = yritysosoite.postinumero
		AND paikkakunta.id = postinumero.paikkakunta
		AND yhteyshenkilo.id = mainostaja.yhteyshenkilo_id;
		
		
	CREATE ROLE taloussihteerirooli;
	GRANT SELECT, UPDATE, INSERT ON Taloussihteeri TO taloussihteerirooli;