// function to open/close nav
function toggleNav(){
  // if nav is open, close it
  if($("nav").is(":visible")){
    $("nav").fadeOut();
    $("button").removeClass("menu");
  } 
  // if nav is closed, open it
  else{
    $("button").addClass("menu");
    $("nav").fadeIn().css('display', 'flex');
  }
}

$('#fuck').click(function(){
  console.log('here')
})

// when clicking + or ☰ button
$("button").click(function(){
//  toggleNav();
  // when clicking ☰ button, open nav
  if($("header").hasClass("open")){
     toggleNav();
     console.log('here I am agai')
  }
  // when clicking + button, open header
  else{ 
    console.log('here I am again')
    $("header").addClass("open");
  } 
});

// close nav
$("#nav-close").click(function(){
  toggleNav();
});

$('#back').click(function() {
  window.location.href=""
})

// scroll to sections
$("nav li").click(function(){
  // get index of clicked li and select according section
  var index = $(this).index();
  var target = $("content section").eq(index);
  
  toggleNav();
  console.log('here')
  $('html,body').delay(300).animate({
    scrollTop: target.offset().top
  }, 500);
});