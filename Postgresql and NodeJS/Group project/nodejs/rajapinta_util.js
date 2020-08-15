// util.js
// ========

module.exports = {

    // runDBQuery - connect to postgresql database and execute an transaction using the connection pool
    // Parameters:
    // query: SQL query to be executed
    // buildHtml: callback function for passing the results to HTML page
    // res: HTTP response - only used in buildHtml callback.
    // resultCollector: JSON object to be passed for HTML rendering - only used in buildHtml callback.
    // postQuery: Query text that is shown in the text field of the form or has been posted with HTTP POST.
    //           -only used in the buildHtml callback.
    runDbQuery: function runDbQuery(query, buildHtml, res, resultCollector) {

        const { Pool } = require('pg')
        const connectionString = "postgres://admin:nobelaner@localhost:5432/i-flac";
        const pool = new Pool({
          connectionString: connectionString,
        })

        // get a pg client from the connection pool
        pool.connect((err, client, done) => {

            if(!client) {
                if(buildHtml != undefined && res != null && res != null) {
                    buildHtml(query, undefined, res, 
                        "Error: No database connection", resultCollector);
                }
                return;
            }

            const shouldAbort = (err) => {
                if (err) {
                    console.error('Error in transaction', err.stack)
                    client.query('ROLLBACK', (err) => {
                      if (err) {
                        console.error('Error rolling back client', err.stack)
                      }
                      // release the client back to the pool
                      done()
                    })

                    // render HTML with the error message
                    if(buildHtml != undefined && res != null) {
                        buildHtml(query, undefined, res, err, resultCollector);
                    }
                }
                return !!err
            }

            // Transaction can lead to multiple callbacks with pg library.
            // You can use async/await approach with pg as well.  
            client.query('BEGIN', (err) => {
                if (shouldAbort(err)) return
                // allow read-only transactions
                client.query('SET TRANSACTION READ WRITE', (err) => {
                    if (shouldAbort(err)) return
                    client.query('SET TRANSACTION ISOLATION LEVEL READ COMMITTED', (err) => {
                        if (shouldAbort(err)) return
                        // run the query - remember to use parameterized queries when needed!
                        client.query(query, (err, result) => {
                            if (shouldAbort(err)) return

                            // console.log(result);

                            client.query('COMMIT', (err) => {
                                if (err) {
                                    console.error('Error committing transaction', err.stack)
                                }
                                // release the client back to the pool
                                done()
                            })
                        // render HTML with result
                        if(buildHtml != undefined && res != null) {
                            buildHtml(result, res, undefined, resultCollector);
                        }
                        });
                    });
                });
            });
        });
    }
}

