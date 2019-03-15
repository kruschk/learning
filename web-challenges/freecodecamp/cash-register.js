function checkCashRegister(price, payment, cid) {
  let changeValues = {
    "PENNY"      :   0.01,
    "NICKEL"     :   0.05,
    "DIME"       :   0.10,
    "QUARTER"    :   0.25,
    "ONE"        :   1.00,
    "FIVE"       :   5.00,
    "TEN"        :  10.00,
    "TWENTY"     :  20.00,
    "ONE HUNDRED": 100.00
  };
  let returnObj = {};
  if (payment < price) {
    returnObj.status = "INSUFFICIENT PAYMENT";
    returnObj.change = [];
    return returnObj;
  }
  let change = payment - price;
  let cidSum = cid.reduce((accumulator, currentValue) => accumulator + currentValue[1], 0);
  if (cidSum < change) {
    returnObj.status = "INSUFFICIENT FUNDS";
    returnObj.change = [];
    return returnObj;
  }
  while (cid[8] - 100.0 >= 0.0) {

  }
  // Here is your change, ma'am.
  return change;
}

// Example cash-in-drawer array:
// [["PENNY", 1.01],
// ["NICKEL", 2.05],
// ["DIME", 3.1],
// ["QUARTER", 4.25],
// ["ONE", 90],
// ["FIVE", 55],
// ["TEN", 20],
// ["TWENTY", 60],
// ["ONE HUNDRED", 100]]

console.clear();
checkCashRegister(19.5, 20, [["PENNY", 1.01], ["NICKEL", 2.05], ["DIME", 3.1], ["QUARTER", 4.25], ["ONE", 90], ["FIVE", 55], ["TEN", 20], ["TWENTY", 60], ["ONE HUNDRED", 100]]);
