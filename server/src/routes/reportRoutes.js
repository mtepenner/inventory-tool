const express = require('express');
const router = express.Router();
const reportController = require('../controllers/reports');

router.get('/inventory', reportController.exportInventoryReport);

module.exports = router;
