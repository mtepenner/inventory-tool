const { getISOWeek, format } = require('date-fns');

// Generates the required format: [mm-dd-yyyy]-WW[ww#]-inventory-report.csv
exports.generateReportFilename = () => {
    const today = new Date();
    const formattedDate = format(today, 'MM-dd-yyyy');
    const workWeek = getISOWeek(today);
    
    return `${formattedDate}-WW${workWeek}-inventory-report.csv`;
};
