BLM 209 Programlama Laboratuvarı I Güz 2019

# Proje 3 : Bağlı Liste Uygulaması

```
Kodlayan: Engin Yenice
```
Coğrafi Bilgi Sistemi
(CBS), dünya üzerindeki karmaşık sosyal,
ekonomik, çevresel vb. sorunların
çözümüne yönelik mekâna/konuma dayalı
karar verme süreçlerinde kullanıcılara
yardımcı olmak üzere, büyük
hacimli coğrafi verilerin; toplanması,
depolanması, işlenmesi, yönetimi,
mekânsal analizi, sorgulaması ve
sunulması fonksiyonlarını yerine getiren
donanım, yazılım, personel, coğrafi veri ve
yöntem bütünüdür. Bu proje kapsamında,
şehirlerin komşuluk ilişkilerini dikkate
alan çok basit bir harita verisi üzerinde
bağlı listelerle ilgili temel işlevleri yerine
getiren bir uygulama yapılması
beklenmektedir.
Bu modelde her bir şehrin dört tane
özelliğe sahip olduğu bilinmektedir:
şehrin ismi, plaka kodu, hangi bölgede
olduğu ve bu şehirden direk ulaşılabilen
(komşu) şehirler. Şehirler arasındaki
komşuluk ilişkisi bir pointer (işaretçi)
yardımıyla tutulabilir. Artık her bir şehir bir bağlı listenin düğümleri şeklinde tutulabilir.

## Şehir Bilgileri ve Komşulukları Tutan Dosyadaki Kayıtların Formatı

Şehirler “sehirler.txt” dosyası içinde aşağıdaki formatta tutulmaktadır:

```
<plaka kodu><,><sehir ismi><,><bulunduğu bolge><,><komşu sehir ismi><,><komşu sehir ismi>..........
```

Bulunduğu bölge için şu kısaltmaları kullanınız: Akdeniz (AK), Doğu Anadolu (DA), Ege (EG), Güneydoğu
Anadolu (GA), İç Anadolu (İA), Marmara (MA) ve Karadeniz (KA).


## Sistem Tasarımı

Tasarlanan sistem 2 çeşit düğüm (node) yapısından oluşturulmalıdır:

- 1. tip (şehir) düğüm yapısında her bir şehir için **plaka kodu (int), şehir adı (string), ait olduğu coğrafi
bölge (string)** ve **komşu sayısı (int)** bilgileri tutulmalıdır.
- 2.tip (komşu) düğüm yapısında her şehir için komşu şehirlerin **plaka kod (int)** bilgilerini ardışık olarak
tutulmalıdır.

Aşağıda örnek bir sistem modeli verilmiştir:

```
Şekil 1. Sistem düğüm yapısı örneği.
```
## Yapılması Gerekenler (İsterler)

- Tasarladığınız sistem yukarıdaki özelliklere sahip sınırsız sayıda şehir bilgisini ve komşuluk bilgisini
tutabilmelidir. Dinamik bir yapıda olmalıdır. (dinamik bellek tahsisine bakınız.) (+ 10 p)
- Tasarlanan sistem ilk başta yukarıda formatı açıklanan “sehirler.txt” dosyasındaki kayıtları okuyarak ve
düğüm yapısını kullanarak modele aktarmalıdır. (+ 15 p)
- Kullanıcı yeni bir şehir, yeni bir komşuluk ekleyebilmelidir. Fakat aynı isimli şehir ve özellikte yeni bir
kayıt eklenmesine sistem izin vermemelidir. (+ 10 p)

NOT: Eklenen şehrin listenin başına veya sonuna denk gelebileceği hesaba katılmalıdır.


- Herhangi bir şehir ismi **veya** plaka kodu ile aratıldığında şehir bilgileri (plaka no, şehir adı, bölgesi,
komşu sayısı) ve komşu şehirlerinin bilgileri (plaka no, şehir adı ve bölgesi) gösterilmelidir. Listede
olmayan bir şehir için arama yapıldığında “şehir listede yok, eklemek ister misiniz?” gibi bir seçenek
sunulmalıdır. (+ 15 p)
- Kullanıcı bir şehri veya komşuluk kaydını silebilmelidir. (Olmayan kayıtların silinmesine sistem izin
vermemelidir.) NOT: Silinecek şehrin listenin başında veya sonunda olabileceği hesaba katılmalıdır.
(+ 10 p)
- Kullanıcı herhangi bir bölgede bulunan şehirlerin bilgilerini (plaka kodu, şehir adı, komşu sayısı)
listeleyebilmelidir. (+ 10 p)
- Belli bir komşu sayısı kriterine uyan şehirler bulunabilmeli ve gösterilmelidir. (Örneğin: 3’ ten fazla
komşusu olan illerin listesi) (+ 10 p)
- Modelin mevcut yapısı “cikti.txt” dosyası içerisinde Şekil 1’ deki gibi diagram biçiminde gösterilmelidir.
(+ 15 p)
- Yukarıdaki tüm isterler kullanıcıya bir menü olarak sunulmalı. Bir işlem yapıldıktan sonra aynı menü
kullanıcı, programdan çıkana kadar tekrar tekrar gösterilmelidir. (+ 5 p)

## Uyarılar

- Düğümler plaka koduna göre ardışık sıralı olmalıdır. (Hem şehir düğümleri hem de komşu düğümler
için)
- Her komşu düğümünün eklenmesi veya silinmesi işleminde şehir düğümünün komşu sayısı bilgisi
güncellenmelidir.
- Programın çıktıları **“cikti.txt”** dosyası içerisine yazdırılmalıdır.
- Proje yalnızca **Standart C** dili kullanılarak yapılacaktır.
- Proje ile ilgili bilgilendirme toplantısına katılımınız ve anlaşılmayan noktaları mutlaka sormanız,
sunumda problem yaşamamanız için çok önemlidir.

## Bonus

- Belli bir sayı aralığında komşu sayısına sahip şehirlerden belirli ortak komşulara sahip olan şehirlerin
listelenmesi (Örneğin: Komşu sayısı 3 ile 7 arasında olan illerden hem Ankara hem de Konya’ya komşu
olan şehirler: Aksaray, Eskişehir) (+10p)


