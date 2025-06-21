" While this may look like gibberish to most, it fulfills
" a purpose I pwomise :3

%s/>/A/g
%s/</E/g
%s/+/U/g
%s/-/O/g
%s/\./e/g
%s/,/a/g
%s/\[/u/g
%s/\]/o/g
if argv(0) == "-sn"
    %s/\n//g
    %s/ //g
end
