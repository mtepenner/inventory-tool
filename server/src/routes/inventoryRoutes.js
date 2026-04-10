const express = require('express');
const router = express.Router();
const inventoryController = require('../controllers/inventory');

router.get('/', inventoryController.getInventory);
router.post('/', inventoryController.addPart);
router.delete('/:ipn', inventoryController.deletePart);

module.exports = router;
