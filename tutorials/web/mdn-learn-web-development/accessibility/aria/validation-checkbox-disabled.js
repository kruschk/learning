var inputs = document.querySelectorAll('input');
var labels = document.querySelectorAll('label');
var form = document.querySelector('form');

var formItems = [];

var errorField = document.querySelector('.errors');
var errorList = document.querySelector('.errors ul');

var checkbox;
var checkboxLabel;

var hiddenAlert = document.querySelector('.hidden-alert');

for(var i = 0; i < inputs.length-1; i++) {
  if(inputs[i].type !== 'checkbox') {
    var obj = {};
    obj.label = labels[i];
    obj.input = inputs[i];
    formItems.push(obj);
  } else {
    checkbox = inputs[i];
    checkboxLabel = labels[i];
  }
}

errorField.style.left = '-100%';

toggleMusician(false);

form.onsubmit = validate;

function validate(e) {
  errorList.innerHTML = '';
  for(var i = 0; i < formItems.length; i++) {
    var testItem = formItems[i];
    if(testItem.input.value === '' && testItem.input.disabled === false) {
      errorField.style.left = '390px';
      createLink(testItem);
    }
  }

  if(errorList.innerHTML !== '') {
    e.preventDefault();
  }
}

function createLink(testItem) {
  var listItem = document.createElement('li');
  var anchor = document.createElement('a');
  anchor.textContent = testItem.input.name + ' field is empty: fill in your ' + testItem.input.name + '.';
  anchor.href = '#' + testItem.input.name;
  anchor.onclick = function() {
    testItem.input.focus();
  };
  listItem.appendChild(anchor);
  errorList.appendChild(listItem);
}

checkbox.onchange = function() {
  if(checkbox.checked) {
    toggleMusician(true);
  } else {
    toggleMusician(false);
  }
};

function toggleMusician(bool) {
  var instruItem = formItems[formItems.length-1];
  if(bool) {
    instruItem.input.disabled = false;
    instruItem.label.style.color = '#000';
    instruItem.input.setAttribute('aria-disabled', 'false');
    hiddenAlert.textContent = 'Instruments played field now enabled; use it to tell us what you play.';
  } else {
    instruItem.input.disabled = true;
    instruItem.label.style.color = '#999';
    instruItem.input.setAttribute('aria-disabled', 'true');
    instruItem.input.removeAttribute('aria-label');
    hiddenAlert.textContent = 'Instruments played field now disabled.';
  }
}
