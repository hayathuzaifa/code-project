// server.js
const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");

const app = express();
app.use(cors());
app.use(bodyParser.json());

// Fake database (replace with MongoDB/MySQL)
const users = [{ email: "your@gmail.com", password: "123456" }];

// Login API
app.post("/api/login", (req, res) => {
  const { email, password } = req.body;

  const user = users.find(u => u.email === email && u.password === password);

  if (user) {
    res.json({ success: true, message: "Login successful", token: "fake-jwt-token" });
  } else {
    res.status(401).json({ success: false, message: "Invalid credentials" });
  }
});

app.listen(3000, () => console.log("Server running on http://localhost:3000"));


