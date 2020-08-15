INSERT INTO lasku (mainoskampanja_id, erapaiva, viitenumero, tilinumero, summa) 
                VALUES (${kampanjaid}, to_date(cast('${erapvm}' as TEXT), 'YYYY-MM-DD'), '${viitenro}', '${tilinro}', ());
    
                SELECT * FROM lasku WHERE viitenumero = '${viitenro}';

--myyjän tiedot
select hkk.nimi from mainoskampanja mk
left join henkilokuntakayttaja hkk on hkk.id = mk.vastuuhlo_id

-- laskun summa
SELECT h.sekuntihinta * count(mn.id) as hinta
from mainoskampanja mk 
left join mainos m on m.mainosk_id = mk.id 
left join mainosnaytto mn on m.id = mn.mainos_id 
left join hinnasto h on h.id = mk.hinnasto_id
where mk.id = {mainoskampanja_id};

--mainostajan tiedot
select yh. from lasku l 
left join mainoskampanja mk on mk.id = l.mainoskampanja_id
left join mainostaja mn on mn.id = mk.mainostaja_id 
left join yritysosoite yo on yo.id = mn.yritysosoite_id
left join yhteyshenkilo yh on yh.id = mn.yhteyshenkilo_id


-- mainokset
Select 
m.nimi, 
m.kesto, 
count(mn.id) as vastaanotettu,
String_agg(Concat(la.alkuklo,'-' ,la.loppuklo), ',') as lahetysajat,
h.sekuntihinta * count(mn.id) as hinta
from mainoskampanja mk 
left join mainos m on m.mainosk_id = mk.id 
left join mainosprofiili mp on mp.id = m.mainosp_id
left join lahetysaika la on la.mainosprofiili_id = mp.id
left join hinnasto h on h.id = mk.hinnasto_id
left join mainosnaytto mn on m.id = mn.mainos_id 
WHERE mk.id = 2
GROUP BY m.id, h.sekuntihinta, m.nimi, m.kesto, mp.id;

-- yhteenveto
Select tilinumero, erapaiva, viitenumero, summa from lasku;


--Näkymä mainostajalle toimitettavia raportteja varten

CREATE VIEW Mainosraportti
AS
  SELECT mja.id                                                AS mainostaja_id,
         m.nimi                                                AS nimi,
         String_agg(Concat(la.alkuklo, la.loppuklo, '-'), ',') AS lahetysajat,
         m.kesto                                               AS kesto,
         Count(mn.id)                                          AS vastaanotettu,
         ( h.sekuntihinta * Count(mn.id) * m.kesto )           AS hinta,
         Date_trunc('month', mn.timestamp)                     AS kuukausi
		 Date_trunc('year', mn.timestamp)					   AS vuosi
  FROM   mainostaja mja
         LEFT JOIN mainoskampanja mk
                ON mk.mainostaja_id = mja.id
         LEFT JOIN hinnasto h
                ON mk.hinnasto_id = h.id
         LEFT JOIN mainos m
                ON m.mainosk_id = mk.id
         LEFT JOIN mainosprofiili mp
                ON m.mainosp_id = mp.id
         LEFT JOIN mainosnaytto mn
                ON mn.mainos_id = m.id
         LEFT JOIN lahetysaika la
                ON la.mainosprofiili_id = mp.id
  GROUP  BY m.id,
            Date_trunc('month', mn.timestamp), Date_trunc('year', mn.timestamp), mja.id, m.nimi, m.kesto, h.sekuntihinta;  

-- Näkymä mainosesitysraportille


-- Laskutettava mainoskampanja
select concat(mk.nimi,': ' ,mk.alkupvm,'-', mk.loppupvm), h.sekuntihinta, mk.maararaha 
from lasku l left join mainoskampanja mk on l.mainoskampanja_id = mk.id left join hinnasto h on mk.hinnasto_id = h.id 
where l.id = ${lasku_id};

CREATE OR replace VIEW mainosesitysraportti
AS
  SELECT To_char(timestamp, 'DD.MM.YYYY') AS Esityspaiva,
         To_char(timestamp, 'HH:MI:SS')   AS Esitysaika,
         a.sukupuoli                      AS Sukupuoli,
         a.ika                            AS Ika,
         a.paikkakunta                    AS Paikkakunta,
         mn.mainos_id                     AS mainos_id
  FROM   mainosnaytto mn
         left join asiakas a
                ON a.id = mn.asiakas_id; 

