var stateObject = {
  "Cluj": ["Cluj-Napoca", "Apahida"],
  "Maramures": ["Baia-Mare", "Recea"]
}

window.onload = function() {
  countySel = document.getElementById("countySel"),
    citySel = document.getElementById("citySel");

  countySel.options[0].text = "Please select county";

  for (var county in stateObject) {
    countySel.options[countySel.options.length] = new Option(county, county);
  }

  countySel.onchange = function() {
    citySel.length = 1;
    citySel.options[0].text = "Please select city"

    if (countySel.selectedIndex == 0) {
      citySel.options[0].text = "Please select county first"
      return;
    }

    var cities = stateObject[this.value];
    for (var i = 0; i < cities.length; ++i) {
      citySel.options[citySel.options.length] = new Option(cities[i], cities[i]);
    }
    if (citySel.options.length == 2) {
      citySel.selectedIndex = 1;
      citySel.onchange();
    }
  }
  countySel.onchange();
}

$(function() {
  var dialog, form,

    // From http://www.whatwg.org/specs/web-apps/current-work/multipage/states-of-the-type-attribute.html#e-mail-state-%28type=email%29
    input1 = $("#input1"),
    input2 = $("#input2"),
    input3 = $("#input3"),
    allFields = $([]).add(input1).add(input2).add(input3),
    tips = $(".validateTips");

  function submit() {
    var s = $("#input1").val();
    s += $("#input2").val();
    s += $("#input3").val();
    paragraph = $("#concatenated-text");
    paragraph.text(paragraph.text() + s);
    dialog.dialog("close");
  }

  dialog = $("#dialog-form").dialog({
    autoOpen: false,
    height: 400,
    width: 350,
    modal: true,
    buttons: {
      "Submit": submit,
      Cancel: function() {
        dialog.dialog("close");
      }
    },
    close: function() {
      form[0].reset();
      allFields.removeClass("ui-state-error");
    }
  });

  form = dialog.find("form").on("submit", function(event) {
    event.preventDefault();
  });

  $("#button").button().on("click", function() {
    dialog.dialog("open");
  });
});