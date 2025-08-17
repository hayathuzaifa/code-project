const express = require('express');
const path = require('path');

const app = express();
const PORT = 3000;

// Serve index.html at root
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

// Example backend API route
app.get('/api/hello', (req, res) => {
  res.json({ message: 'Hello from the backend!' });
});

app.listen(PORT, '0.0.0.0', () => {
  console.log(`Server running at http://localhost:${PORT}`);
});