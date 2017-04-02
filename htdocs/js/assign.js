var ans;
var prb;
var lim = -1;
var num = 0;

function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}

$(document).ready(function(){
	if(readCookie("id") != null) {
		$("#login_form").hide();
		$("#register").hide();
		$("#logout").show();
		$("#history").show();
		$.ajax({
        	url : 'get_mode.php'
   		 }).done(function(data) {
   		 	if(parseInt(data) == 2)
   		 		$("#group").show();
   		 });
	}
	
	var bnum = 5;
    $("#button1").click(function(){ 
		$("#button1").toggleClass("btn-success");
		if($("#hidd1").val() == "1")
			$("#hidd1").val("0");
		else
			$("#hidd1").val("1");
	});
	$("#button2").click(function(){ 
		$("#button2").toggleClass("btn-success");
		if($("#hidd2").val() == "1")
			$("#hidd2").val("0");
		else
			$("#hidd2").val("1");
	});
	$("#button3").click(function(){ 
		$("#button3").toggleClass("btn-success");
		if($("#hidd3").val() == "1")
			$("#hidd3").val("0");
		else
			$("#hidd3").val("1");
	});
 	$("#button4").click(function(){ 
		$("#button4").toggleClass("btn-success");
		if($("#hidd4").val() == "1")
			$("#hidd4").val("0");
		else
			$("#hidd4").val("1");
	});
	$("#button5").click(function(){ 
		$("#button4").toggleClass("btn-success");
		if($("#hidd4").val() == "1")
			$("#hidd4").val("0");
		else
			$("#hidd4").val("1");
	});
	$("#button_all").click(function(){ 
		for(var i = 1; i <= bnum; i++) {
			$("#button" + i.toString() + "").addClass("btn-success");
			if($("#hidd" + i.toString() + "").val() == "1")
				$("#hidd" + i.toString() + "").val("0");
			else
				$("#hidd" + i.toString() + "").val("1");
		}
			
	});
	
	$("#diff1").click(function(){ 
		$("#diff").val(1);
		document.getElementById("down").innerHTML="Difficulty: 1";
//		$("#down").toggleClass("btn-primary");
	});
	
	$("#diff2").click(function(){ 
		$("#diff").val(2);
		document.getElementById("down").innerHTML="Difficulty: 2";
//		$("#down").toggleClass("btn-primary");
	});
	
	$("#diff3").click(function(){ 
		$("#diff").val(3);
		document.getElementById("down").innerHTML="Difficulty: 3";
//		$("#down").toggleClass("btn-warning");
	});
	
	$("#diff4").click(function(){ 
		$("#diff").val(4);
		document.getElementById("down").innerHTML="Difficulty: 4";
//		$("#down").toggleClass("btn-warning");
	});
	
	$("#diff5").click(function(){ 
		$("#diff").val(5);
		document.getElementById("down").innerHTML="Difficulty: 5";
//		$("#down").toggleClass("btn-danger");
	});
	
	
	
	$("#button_gen").click(function() {
  		$("#problem").show()
  		$("#input_side").show()
  		$("#counter").show()
  		$("#good_ans").hide()
  		$("#bad_ans").hide()
  		$("#solution").hide()
  		$("#steps").hide()
  		$("#answer").val("")
  		$.post("backend.php", {
  			q: 1,
  			pi: 1,
  			e: 1,
  			id: 1,
  			add: 1,
  			neg: 1,
  			inv: 1,
  			parts: $("#hidd1").val(),
  			exp: $("#hidd2").val(),
			log: $("#hidd3").val(),
			sine: $("#hidd4").val(),
			cosine: $("#hidd4").val(),
			asine: $("#hidd5").val(),
			atan: $("#hidd5").val(),
			diff: $("#diff").val(),
  		},function(data, status) {
   		 	prb = data.split(/[\n]+/)[0];
       		document.getElementById("problem").innerHTML=prb;
       		ans = data.split(/[\n]+/)[1];
       		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
   		 });
	});
	$("#solution").click(function(){ 
		$("#steps").show()
	});
});

function check_answer() {
	var s = document.forms["ans_form"]["answer"].value;
	if(readCookie("id") != null) {
		$.post("update_history.php", 
		{
			problem: prb,
        	user_answer: s,
        	correct_answer: ans	
        }, function(data, status){});
	}
    if (s == ans) {
    	var cur = $("#correct").val();
    	$("#correct").val(parseInt(cur) + 1);
   		$("#bad_ans").hide();
        $("#good_ans").show();
    }
    else {
    	$("#bad_ans").show();
        $("#good_ans").hide();
    }
    $("#solution").show()
//    alert(lim);
	lim = parseInt($("#hidd").val());
    num += 1;
    document.getElementById("bubble").innerHTML=num.toString() + "/" + lim.toString();
//    alert(lim);
    if (num == lim)
    {
    	$("#button_gen").attr("disabled", true);
    	$("#end_assignment").show();
    	$.post("set_score.php", 
		{
			ind: $("#ind").val(),
			score: Math.round($("#correct").val()*100.0/$("#hidd").val())
        }, function(data, status){});
    }
    return false;
}