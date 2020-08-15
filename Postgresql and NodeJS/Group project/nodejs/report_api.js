//
// node.js example for Tietokantojen suunnittelu
//
// Install required packages (see package.json) by running: npm install
//
// Edit connectionString in util.js with your postgresql information: 
// var connectionString = "postgres://user:pass@localhost:port/dbname";
//
// Start node server: node rajapinta.js
// Quick test in linux-desktop.cc.tut.fi on command line by typing: curl tkannatX.cs.tut.fi:8888
//
// Note! 
// - To execute any changes on the source code, you must restart the node server. 
// - Pug files can be modified without restart.
// - Any unhandled error will crash the server.
//

const getMainostajat = "SELECT * FROM Mainostaja";
const getMainokset = "SELECT * FROM mainos";
const getKkRaportti = "SELECT * FROM Mainosraportti";

var util = require('./rajapinta_util');
var express = require('express');
var router = express.Router();
var bodyParser = require('body-parser');
router.use(bodyParser.urlencoded({ extended: false }));

// route - HTTP GET to http://tkannatX.cs.tut.fi:8888/    
router.get('/mainostajat', function (req, res) {
	try {
		// resultCollector collects the contents that will be rendered on the WWW page.
		var resultCollector = {}; 
		var query = getMainostajat;
		util.runDbQuery(query, showResult2, res, resultCollector);
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
});

router.get('/mainokset', function (req, res) {
	try {
		// resultCollector collects the contents that will be rendered on the WWW page.
		var resultCollector = {}; 
		var query = getMainokset;
		util.runDbQuery(query, showResult2, res, resultCollector);
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
});

router.get('/kkraportti', function (req, res) {
	try {
		// resultCollector collects the contents that will be rendered on the WWW page.
		var resultCollector = {}; 
		var query = getKkRaportti;
		var filters = [];
		var vuosi = req.query.vuosi;
		var kk = req.query.kk;
		var mainostaja_id = req.query.mainostaja;
		var kkQuery = "SELECT * FROM Mainosraportti WHERE mainostaja_id = " + mainostaja_id + " AND kuukausi = '" + kk + "' AND vuosi = '" + vuosi + "'";

		util.runDbQuery(kkQuery, showResult2, res, resultCollector);
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
});

router.get('/mainosesitysraportti', function (req, res) {
	try {
	
		// resultCollector collects the contents that will be rendered on the WWW page.
		var resultCollector = {}; 
		var query = "SELECT mn.nimi AS mainostaja, mk.nimi as mainoskampanja, m.nimi as mainos FROM Mainos m LEFT JOIN Mainoskampanja mk ON mk.id = m.mainosk_id LEFT JOIN Mainostaja mn ON mn.id = mk.mainostaja_id ";
		var mainos = req.query.mainos;
		query += "WHERE m.id = " + mainos +";";
		query += "SELECT "
		var columns = [];
		if(Object.keys(req.query).length !== 0) {
		
		var esityspaiva = req.query.esityspaiva;
		if(esityspaiva == 1) {
			columns.push("Esityspaiva")
		}
		var esitysaika = req.query.esitysaika;
		if(esitysaika == 1) {
			columns.push("Esitysaika");
		}
		var sukupuoli = req.query.sukupuoli;
		if(sukupuoli == 1) {
			columns.push("Sukupuoli");
		}
		var ika = req.query.ika;
		if(ika == 1) {
			columns.push("Ika");
		}
		
		var paikkakunta = req.query.paikkakunta;
		if(paikkakunta == 1) {
			columns.push("Paikkakunta");
		}
		query += columns.join(", ");
		}
		
		query += " FROM Mainosesitysraportti WHERE mainos_id =" + mainos + ";";
		console.log(query);
		
		
		util.runDbQuery(query, showResultJSON, res, resultCollector);
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
});


// showResult - return results of the query to browser.
// Parameters:
// dbResult: results of database query, these are added to dropdown menu
// res: HTTP response
// err: database error message 
// resultCollector: collecting content to be rendered
function showResult2(dbResult, res, err, resultCollector) {
	try {
		resultCollector.result = dbResult;

		resultCollector.title = 'Oispa_kaljaa Tietokantahakuja';
		resultCollector.message = 'Raporttimoduulin tulostuksia taulukkona';
		resultCollector.error = err;

		//You can try this as well:
		//res.send(JSON.stringify(dbResult.rows));
		//...however, mostly likely the output needs
		//some kind of better formatting.

		//Send the content to a view named 'rajapinta_simple' 
		res.render('rajapinta_simple', resultCollector);
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}

function showResultJSON(dbResult, res, err, resultCollector) {
	try {
		resultCollector.result = dbResult;

		resultCollector.title = 'Oispa_kaljaa tietokantahakuja';
		resultCollector.message = 'Raporttimoduulin Json-tyyppisiä tulostuksia';
		resultCollector.error = err;

		res.send('<p>' +"Mainostaja:" + JSON.stringify(dbResult[0].rows[0].mainostaja, null, 4)+ '</p> <br>' +
		'<p>' +"Mainoskampanja:" + JSON.stringify(dbResult[0].rows[0].mainoskampanja)+ '</p> <br>' +
		'<p>' +"Mainos:" + JSON.stringify(dbResult[0].rows[0].mainos)+ '</p> <br>' +
		'<pre>' + JSON.stringify(dbResult[1].rows, null, 4) + '</pre>');
	
	} catch (error) {            
        res.status(500).send("DB haku ei onnistunut! Tarkista parametrit.");
    }
}

module.exports = router;