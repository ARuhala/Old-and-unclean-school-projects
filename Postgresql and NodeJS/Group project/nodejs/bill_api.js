const getlaskutus = "SELECT * from lasku";

var util = require('./rajapinta_util');
var express = require('express');
var app = express();
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: false }));

app.set('views', './views');
app.set('view engine', 'pug');

app.get('/', function (req, res) {
    
    res.redirect('/etusivu');

});

app.get('/etusivu', function (req, res) {

    try {
    // rendering without resultCollector
        res.render('etusivu', {
            title: 'Oispa_kaljaa etusivu',
            message: 'Toteutetut rajapintalinkit'
        });

    } catch (error) {
            
        res.status(500).send("Etusivua ei löytynyt!");
    }
});

app.get('/laskutus', function (req, res) {
    try {
        // resultCollector collects the contents that will be rendered on the WWW page.
        var resultCollector = {}; 

        //How to handle URL parameter such as http://tkannat7.cs.tut.fi:8888/?lasku=3
        var laskuid = req.query.lasku;
        if (laskuid == null) { 
            query = getlaskutus; 
        }
        else { 
            query = `SELECT * FROM lasku WHERE id = ${laskuid};`; 
        }

        // run query

        util.runDbQuery(query, showResult, res, resultCollector);
    } catch (error) {
            
        res.status(500).send("Hups virhe!");
    }
});

// http://tkannat7.cs.tut.fi:8888/lisaa?kampanja=4&erapvm=2019-04-15&viitenro=037645348439&tilinro=8385579
app.get('/lisaa', function (req, res) {

    try {
        // resultCollector collects the contents that will be rendered on the WWW page.
        var resultCollector = {}; 


        if (Object.keys(req.query).length == 0) { 
            query = 'SELECT * FROM mainoskampanja WHERE id NOT IN (select mainoskampanja_id FROM lasku);' 
            util.runDbQuery(query, showResult, res, resultCollector);
        }
        else {

            try {
                var kampanjaid = req.query.kampanja;
                var erapvm = req.query.erapvm.toString();
                var viitenro = req.query.viitenro;
                var tilinro = req.query.tilinro;

                const summaquery = `
                    SELECT h.sekuntihinta * count(mn.id) as hinta
                    from mainoskampanja mk 
                    left join mainos m on m.mainosk_id = mk.id 
                    left join mainosnaytto mn on m.id = mn.mainos_id 
                    left join hinnasto h on h.id = mk.hinnasto_id
                    where mk.id = ${kampanjaid}
                    GROUP BY h.sekuntihinta
                `;
        
                const insertquery = `
                    INSERT INTO lasku (mainoskampanja_id, erapaiva, viitenumero, tilinumero, summa) 
                    VALUES (${kampanjaid}, to_date(cast('${erapvm}' as TEXT), 'YYYY-MM-DD'), '${viitenro}', '${tilinro}', (${summaquery}));
        
                    SELECT * FROM lasku WHERE viitenumero = '${viitenro}';
                `;
        
                util.runDbQuery(insertquery, showResultOfSecondQuery, res, resultCollector);
            } catch (error) {
                
                res.status(500).send("Hups virhe!");
            }
        }

    } catch (error) {
            
        res.status(500).send("Hups virhe!");
    }
});

app.get('/muokkaa', function (req, res) {

    try {
        // http://tkannatX.cs.tut.fi/muokkaa?lasku=<laskun tunniste>&<muokattava ominaisuus>=<uusi arvo>&...(Huom: ominaisuuksia voi olla useampia)
        // selain näyttää tunnisteen mukaisen laskun muokattuine arvoineen.
        var laskuid = req.query.lasku;
        var resultCollector = {}; 
        
        var changepool = new Map();
        if (req.query.viitenumero != null)
        {
            changepool.set('viitenumero', `'${req.query.viitenumero}'`);
        }

        if(req.query.erapvm != null)
        {
            changepool.set('erapaiva', `to_date(cast('${req.query.erapvm}' as TEXT), 'YYYY-MM-DD')`);
        }

        changepool.set('tilinumero', req.query.tilinumero);
        changepool.set('maksettu', req.query.maksettu);
        changepool.set('summa', req.query.summa).set('karhu',req.query.karhu);
        changepool.set('lahetetty', req.query.lahetetty).set('mainoskampanja_id', req.query.mainoskampanjan_id);

        // muodostetaan changestringin sisältö
        var changestring = '';
        var index = 0;
        var iterator1 = changepool.keys();
        changepool.forEach(element => {
            var pair = iterator1.next();
            if (changepool.get(pair.value) != null) 
            {            
                if (index > 0)
                {
                    changestring = changestring.concat(', ');
                }           
                changestring = changestring.concat(`${pair.value} = ${changepool.get(pair.value)}`);
                index = index + 1;
            }    
        });

        var query = `UPDATE lasku SET ${changestring} WHERE id = ${laskuid};  SELECT * FROM lasku WHERE id = ${laskuid};`;

        // run query
        util.runDbQuery(query, showResultOfSecondQuery, res, resultCollector);

    } catch (error) {
            
        res.status(500).send("Hups virhe!");
    }
});

app.get('/laheta', function (req, res) {
    try {

        var resultCollector = {};
        var laskuid = req.query.lasku;
        var query = `Select m.nimi, m.kesto, count(mn.id) as vastaanotettu, h.sekuntihinta * count(mn.id) as hinta
                        from lasku l
                        left join mainoskampanja mk on mk.id =l.mainoskampanja_id
                        left join mainos m on m.mainosk_id = mk.id
                        left join mainosnaytto mn on m.id = mn.mainos_id
                        left join hinnasto h on h.id = mk.hinnasto_id
                        WHERE l.id = ${laskuid}
                        GROUP BY m.id, h.sekuntihinta, m.nimi, m.kesto;

                    --myyjan tiedot
                    select hkk.nimi from lasku l
                        left join mainoskampanja mk on mk.id = l.mainoskampanja_id
                        left join henkilokuntakayttaja hkk on hkk.id = mk.vastuuhlo_id
                        WHERE l.id = 2;

                    --yhteenveto
                    Select tilinumero, erapaiva, viitenumero, summa
                        from lasku
                        WHERE lasku.id = ${laskuid};

                    --mainostajan tiedot
                    select yh.nimi, yh.yrityksen_nimi, yo.katuosoite, yo.postinumero
                        from lasku l
                        left join mainoskampanja mk on mk.id = l.mainoskampanja_id
                        left join mainostaja mn on mn.id = mk.mainostaja_id
                        left join yritysosoite yo on yo.id = mn.yritysosoite_id
                        left join yhteyshenkilo yh on yh.id = mn.yhteyshenkilo_id
                        WHERE l.id = ${laskuid};

                    select concat(mk.nimi,': ' ,mk.alkupvm,'-', mk.loppupvm), h.sekuntihinta, mk.maararaha 
                        from lasku l left join mainoskampanja mk on l.mainoskampanja_id = mk.id left join hinnasto h on mk.hinnasto_id = h.id 
                        where l.id = ${laskuid};
        `;

        util.runDbQuery(query, showResultLahettaminen, res, resultCollector);

    } catch (error) {
            
        res.status(500).send("Hups virhe!");
    }
});

app.get('/poista', function (req, res) {
    try {
        // http://tkannatX.cs.tut.fi/poista?lasku=<laskun tunniste>
        var resultCollector = {}; 
        var laskuid = req.query.lasku;

        query = `DELETE FROM lasku WHERE id = ${laskuid};`;
        util.runDbQuery(query, showResultPoistaminen, res, resultCollector);

    } catch (error) {
            
        res.status(500).send("Hups virhe!");
    }
});

app.get('/karhulasku', function (req, res) {
    try {
        // resultCollector collects the contents that will be rendered on the WWW page.
        // http://tkannatX.cs.tut.fi/karhulasku?lasku=<laskun tunniste>&erapvm=<pvm formaatissa yyyy-mm-dd>&viitenro=<jonkinlainen viitenro>&viivastys=<viivastysmaksun suuruus>
        var resultCollector = {}; 

            var laskuid = req.query.lasku;
            var erapvm = req.query.erapvm.toString();
            var viitenro = req.query.viitenro;
            var viivastys = req.query.viivastys;

        query =`
            UPDATE lasku SET summa = summa + ${viivastys}, karhu = true, erapaiva = to_date(cast('${erapvm}' as TEXT), 'YYYY-MM-DD'), viitenumero = '${viitenro}'
                WHERE id = ${laskuid};
                SELECT * FROM lasku WHERE id = ${laskuid};
        `;
            util.runDbQuery(query, showResultOfSecondQuery, res, resultCollector);
    } catch (error) {
        
        res.status(500).send("Hups virhe!");
    }
});



// showResult - return results of the query to browser.
// Parameters:
// dbResult: results of database query, these are added to dropdown menu
// res: HTTP response
// err: database error message 
// resultCollector: collecting content to be rendered
function showResult(dbResult, res, err, resultCollector) {
    try {
        resultCollector.result = dbResult;

        resultCollector.title = 'Oispa_kaljaa tietokantahakuja';
        resultCollector.message = 'Rajapintatoteutuksen mukaisia tulostuksia';
        resultCollector.error = err;

        res.render('rajapinta_simple', resultCollector);

    } catch (error) {
            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}

function showResultOfSecondQuery(dbResult, res, err, resultCollector) {
    try {

    resultCollector.result = dbResult;

    resultCollector.title = 'Oispa_kaljaa tietokantahakuja';
    resultCollector.message = 'Rajapintatoteutuksen mukaisia tulostuksia';
    resultCollector.error = err;

    res.send('<pre>' + JSON.stringify(dbResult[1].rows, null, 4) + '</pre>');

    } catch (error) {
                
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}

function showResultLahettaminen(dbResult, res, err, resultCollector) {
    try {

        resultCollector.result = dbResult[0];

        resultCollector.title = 'Oispa_kaljaa tietokantahakuja';
        resultCollector.message = 'Rajapintatoteutuksen mukaisia tulostuksia';
        resultCollector.error = err;

        resultCollector.mainoskampanjanmyyja = dbResult[1].rows[0].nimi;

        resultCollector.tilinumero = dbResult[2].rows[0].tilinumero;
        resultCollector.erapaiva = dbResult[2].rows[0].erapaiva;
        resultCollector.viitenumero = dbResult[2].rows[0].viitenumero;
        resultCollector.summa = dbResult[2].rows[0].summa;

        resultCollector.mainoksenostaja = dbResult[3].rows[0].nimi;
        resultCollector.yrityksen_nimi = dbResult[3].rows[0].yrityksen_nimi;
        resultCollector.postinumero = dbResult[3].rows[0].postinumero;
        resultCollector.katuosoite = dbResult[3].rows[0].katuosoite;

        resultCollector.kampanjanimijapvm = dbResult[4].rows[0].concat;
        resultCollector.sekuntihinta = dbResult[4].rows[0].sekuntihinta;
        resultCollector.maararaha = dbResult[4].rows[0].maararaha;

        res.render('lahettaminen', resultCollector);

    } catch (error) {
                
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}


function showResultPoistaminen(dbResult, res, err, resultCollector) {
    try {

        resultCollector.result = dbResult;

        resultCollector.title = 'Oispa_kaljaa tietokantahakuja';
        resultCollector.message = 'Laskun poistaminen onnistui';
        resultCollector.error = err;
    
        res.render('poistaminen', resultCollector);
    } catch (error) {
                
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}

app.use(require('./report_api'));

// Binds and listens for connections on the specified port.
app.listen(8888, function () {
    console.log('Oispa_kaljaa app listening on port 8888');
});

