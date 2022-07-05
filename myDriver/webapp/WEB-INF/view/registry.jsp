<%@ page language="java" import="java.util.*" pageEncoding="utf-8" %>
<html>
<head>
    <title>注册</title>
    <script src="${pageContext.request.contextPath}/js/jquery.js"></script>
    <script>

        $(function () {
            $("#submit").on('click', function () {
                $.ajax({
                    url: "/registry",
                    type: 'POST',
                    data: {'name': $("#username").val(), 'password': $("#password").val()},
                    success: function (data) {
                        alert(data);
                    }
                });
            })
        });

    </script>
</head>
<body>
<h2>注册</h2>
用户名<input id="username" type="text"/>
密码<input id="password" type="password"/>
<input id="submit" type="submit" value="提交"/>
</body>
</html>
