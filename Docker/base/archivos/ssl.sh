#!/usr/bin/expect

spawn openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/apache2/ssl/Oesterheld/apache.pem -out /etc/apache2/ssl/Oesterheld/apache.pem


set country "AR"
set state "Buenos Aires"
set locality "La Plata"
set organization "Oesterheld"
set organization_unit "biblioteca"
set common_name "oesterheld.olgavazquez"
set email "a@b.com"


expect {
       "Country Name (2 letter code)"
}
send "$country\n"

expect {
       "State or Province Name (full name)"
}
send "$state\n"

expect {
       "Locality Name (eg, city)"
}
send "$locality\n"

expect {
       "Organization Name (eg, company)"
}
send "$organization\n"

expect {
       "Organizational Unit Name (eg, section)"
}
send "$organization_unit\n"

expect {
    "Common Name (eg, YOUR name)"
}
send "$common_name\n"

expect {
       "Email Address"
}
send "$email\n"

expect eof
