var webdriver = require('selenium-webdriver'),
    By = webdriver.By,
    until = webdriver.until;

var driver = new webdriver.Builder()
    .forBrowser('firefox')
    .build();

driver.get('http://mdn.github.io/learning-area/tools-testing/cross-browser-testing/accessibility/native-keyboard-accessibility.html');

var button = driver.findElement(By.css('button:nth-of-type(1)'));

button.click();

var alert = driver.switchTo().alert();

alert.getText().then(function(text) {
  console.log('Alert text is \'' + text + '\'');
});

alert.accept();

var input = driver.findElement(By.id('input1'));

driver.sleep(2000).then(function() {
  input.sendKeys('Filling in my form');
  input.getAttribute("value").then(function(value) {
    if(value !== '') {
      console.log('Form input editable');
    }
  });
});

driver.quit();
