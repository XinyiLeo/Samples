function calling = hw_3ex1(number)
million = floor(number/(1000000));
ww=mod(number,1000000*million);
thousand = floor(ww/1000);
h=mod(ww,1000*thousand);

if million == 0
    if thousand == 0
        calling = (hundred(h));
    else 
        calling = strcat(hundred(thousand),' thousand and',hundred(h));
    end
else 
    if thousand == 0
        calling = strcat(hundred(million),' million and',hundred(h));
    else 
        calling = strcat(hundred(million),' million and',hundred(thousand) ,' thousand and',hundred(h));
    end
end
function hh = hundred(h)
hi = floor(h/100); 
m = mod(h,100*hi);
switch hi
    case 1
        hh=strcat(' one hundred',tenone(m));
    case 2
        hh=strcat(' two hundred',tenone(m));
    case 3
        hh=strcat(' three hundred',tenone(m));
    case 4
        hh=strcat(' four hundred',tenone(m)); 
    case 5
        hh=strcat(' five hundred',tenone(m)); 
    case 6
        hh=strcat(' six hundred',tenone(m)); 
    case 7
        hh=strcat(' seven hundred',tenone(m)); 
    case 8
        hh=strcat(' eight hundred',tenone(m)); 
    case 9
        hh=strcat(' nine hundred',tenone(m)); 
    case 0
        hh=(tenone(m)); 
end

function mm = tenone(m)
n = floor(m/10);
l = mod(m,n*10);
switch n
    case 1 
        switch l
            case 1 
                mm=(' eleven');
            case 2 
                mm=(' twelve');
            case 3 
                mm=(' thirteen');
            case 4
                mm=(' fourteen');
            case 5
                mm=(' fifteen');
            case 6
                mm=(' sixteen');
            case 7
                mm=(' seventeen');
            case 8
                mm=(' eighteen');
            case 9
                mm=(' ninteen');
            case 0
                mm=(' ten');
        end
    case 2 
        mm = strcat(' twenty',unitd(l));
    case 3
        mm = strcat(' thirty',unitd(l));
    case 4
        mm = strcat(' fourty',unitd(l));
    case 5
        mm = strcat(' fifty',unitd(l));
    case 6
        mm = strcat(' sixty',unitd(l));
    case 7
        mm = strcat(' seventy',unitd(l));
    case 8
        mm = strcat(' eighty',unitd(l));
    case 9
        mm = strcat(' ninty',unitd(l));
    case 0
        mm = (unitd(l));
end

function ll = unitd(l)
switch l
    case 1
        ll=(' one');
    case 2
        ll=(' two');
    case 3
        ll=(' three');
    case 4
        ll=(' four');
    case 5
        ll=(' five');
    case 6
        ll=(' six');
    case 7
        ll=(' seven');
    case 8
        ll=(' eight');
    case 9
        ll=(' nine');
    case 0
        ll=(' ');
        
end
end
end       
end
if number ==0
    calling = ('zero');
end

end



