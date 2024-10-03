const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

const app = express();
const port = process.env.PORT || 3000;

mongoose.connect('mongodb+srv://coderfromheart:OwZLyOldBwVqODg0@cluster0.42q9esz.mongodb.net/', {
    dbName: "ESP8266"
})
.then(() => {
    console.log("Database Connection Successfull");
})
.catch((err) => {
    console.log("Database Connection Failed: ", err); 
}); 


const DataSchema = new mongoose.Schema({
  value: {
    type: String,
    required: true
  },
  timestamp: {
    type: Date,
    default: Date.now
  }
});

const Data = mongoose.model('Data', DataSchema);


app.use(bodyParser.json());

app.post('/data', async (req, res) => {
  const { value } = req.body;

  try {
    const newData = new Data({ value });
    await newData.save();
    res.status(201).json({ message: 'Data saved successfully!' });
  } catch (err) {
    res.status(500).json({ message: 'Failed to save data', error: err.message });
  }
});

app.get('/data', async (req, res) => {
  try {
    const data = await Data.find();
    res.status(200).json(data);
  } catch (err) {
    res.status(500).json({ message: 'Failed to retrieve data', error: err.message });
  }
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
