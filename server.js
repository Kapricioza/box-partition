const express = require('express');
const app = express();
const port = 3000;
const {exec} = require('child_process');
const path = require('path');
const { error } = require('console');

app.use(express.static('web'));
app.use(express.json());

app.post('/run-backend', (req, res) =>{
    const {m ,n , k} = req.body;
    const execPath = path.join(__dirname, 'bin', 'main.exe');
    const command = `"${execPath}" ${m} ${n} ${k}`;

    console.log(`Executing: ${command}`);

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution error: ${error.message}`);
            return res.status(500).json({ error: 'Execution failed' });
        }

        if (stderr) {   
            console.error(`Execution stderr: ${stderr}`);
            return res.status(500).json({ error: 'Execution error', details: stderr });
        }

        console.log(`Execution complete: ${stdout}`);
        res.json({message:`Execution complete`,output: stdout });

    });
});

app.listen(port,() =>{
    console.log(`Server is running on http://localhost:${port}`);
})