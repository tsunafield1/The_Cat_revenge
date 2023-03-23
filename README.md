# The Cat's revenge
โปรเจคนี้มีชื่อว่า "The Cat's revenge" ทำขึ้นเพื่อสร้างเกมจากภาษา C++ ด้วย Visual Studio โดยใช้ SFML 2.5.1

![alt text](https://github.com/tsunafield1/The_Cat_revenge/blob/master/Infographics.png?raw=true)

โดยหลักการทำงานของเกม คือ ใช้ while loop ครอบการตรวจสอบเงื่อนไข และการควบคุมต่างๆ เอาไว้ เพื่อให้เกมเกิดทำงานซ้ำต่อไปเรื่อยๆ

คลิปนำเสนอผลงาน: https://youtu.be/7bJJT_t7gRo

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ใน GameDev มี 7 โฟลเดอร์ และ 1 ไฟล์ (.cpp)
- assets คือ โฟลเดอร์เก็บไฟล์ภาพ assets (.png) ที่ใช้ในเกม
- effects คือ โฟลเดอร์เก็บไฟล์ภาพ effects (.png) ที่ใช้ในเกม
- fonts คือ โฟลเดอร์เก็บไฟล์ font (.TTF) ที่ใช้ในเกม
- highscore คือ โฟลเดอร์เก็บข้อมูลคะแนนใน Leaderboard (.txt) ของเกม
- maps คือ โฟลเดอร์เก็บไฟล์ภาพ block และ background (.png) ที่ใช้ในเกม
- sounds คือ โฟลเดอร์เก็บไฟล์เสียงที่ใช้ในเกม (.ogg) แบ่งเป็น effects และ musics
- sprites คือ โฟลเดอร์เก็บไฟล์ภาพ sprite (.jpg และ .png) ที่ใช้ในเกม
- Source.cpp คือ ไฟล์โค้ดของโปรเจค

ใน GameDev/Source.cpp มี 11 class
- GROUND คือ class ที่ใช้สำหรับสร้างพื้นในเกม
- Fish คือ class ที่ใช้สำหรับสร้าง และทำลายปลาในเกม
- Fishbone คือ class ที่ใช้สำหรับสร้าง และทำลายก้างปลาในเกม
- normalBear คือ class ที่ใช้สำหรับสร้าง และควบคุมหมีชนิดที่ 1 ในเกม
- throwBear คือ class ที่ใช้สำหรับสร้าง และควบคุมหมีชนิดที่ 2 ในเกม
- boss1Bear คือ class ที่ใช้สำหรับสร้าง และควบคุมบอสหมีชนิดที่ 1 ในเกม
- boss2Bear คือ class ที่ใช้สำหรับสร้าง และควบคุมบอสหมีชนิดที่ 2 ในเกม
- boss3Bear คือ class ที่ใช้สำหรับสร้าง และควบคุมบอสหมีชนิดที่ 3 ในเกม
- item คือ class ที่ใช้สำหรับสร้าง และควบคุมไอเทมพิเศษในเกม
- chest คือ class ที่ใช้สำหรับสร้าง และควบคุมหีบสมบัติในเกม

มี 46 function
- void mainCharacter() คือ function ที่ใช้สำหรับสร้างแอนิเมชั่น และควบคุมสิ่งต่างๆ ของตัวละครหลัก
- void damageCal() คือ function ที่ใช้สำหรับคำนวณการได้รับดาเมจของตัวละครหลัก
- void shoot() คือ function ที่ใช้สำหรับควบคุมการขว้างก้างปลาของตัวละครหลัก
- void setText() คือ function ที่ใช้สำหรับเปลี่ยนสถานะต่างๆ เป็น string เพื่อนำไปแสดงต่อไป
- std::string changeNtoS(int, int) คือ function ที่ใช้สำหรับเปลี่ยนตัวเลขเป็น string โดยที่กำหนดจำนวนหลักได้
- std::string changeNtoS(int) คือ function ที่ใช้สำหรับเปลี่ยนตัวเลขเป็น string
- void scratch() คือ function ที่ใช้สำหรับควบคุมการข่วนของตัวละครหลัก
- void loadTexture() คือ function ที่ใช้สำหรับโหลดรูปภาพมาเก็บในตัวแปรต่างๆ
- void setSprite() คือ function ที่ใช้สำหรับใส่ texture และกำหนดขนาดของสิ่งต่างๆในเกม
- void firstTextSet() คือ function ที่ใช้สำหรับกำหนดคุณสมบัติของตัวอักษรในเกม
- void setGround1() คือ function ที่ใช้สำหรับสร้างพื้นของด่าน 1
- void setMonster1() คือ function ที่ใช้สำหรับสร้างหมีของด่าน 1
- void setFish1() คือ function ที่ใช้สำหรับสร้างปลาของด่าน 1
- void collectFish() คือ function ที่ใช้สำหรับการเก็บปลาของตัวละครหลัก
- void setChest1() คือ function ที่ใช้สำหรับสร้างหีบสมบัติของด่าน 1
- void use(int) คือ function ที่ใช้สำหรับการใช้ไอเทมพิเศษ
- void setHead() คือ function ที่ใช้สำหรับสร้างแถบสถานะของตัวละครหลักในเกม
- void stage1() คือ function ที่ใช้สำหรับสร้างด่าน 1
- void setup() คือ function ที่ใช้สำหรับเตรียมพร้อมสิ่งต่างๆ ก่อนที่จะเริ่มเกม
- void start() คือ function ที่ใช้สำหรับกำหนดสถานะต่างๆ ให้เป็นสถานะเริ่มต้น
- void reset() คือ function ที่ใช้สำหรับลบสิ่งต่างๆที่สร้างไว้ และล้างสถานะพิเศษ
- void leaderboard() คือ function ที่ใช้สำหรับสร้าง และควบคุมการทำงานใน Leaderboard
- void MENU() คือ function ที่ใช้สำหรับสร้าง และควบคุมการทำงานใน Menu
- void exitFromMenu() คือ function ที่ใช้สำหรับสร้าง และควบคุมการทำงานใน Exit
- void gameDraw() คือ function ที่ใช้สำหรับวาด object ต่างๆ ในเกมขึ้นบนจอ
- void gameCal() คือ function ที่ใช้สำหรับคำนวณระบบต่างๆ ในเกม
- void gamePause() คือ function ที่ใช้สำหรับสร้าง และควบคุมการทำงานใน Pause menu
- void startdata() คือ function ที่ใช้สำหรับรีเซตข้อมูลใน Leaderboard
- void gameover() คือ function ที่ใช้สำหรับสร้าง และควบคุมการทำงานใน Game over
- void stage1boss() คือ function ที่ใช้สำหรับสร้าง และกำหนดพื้นที่ สำหรับบอสด่าน 1
- void shop() คือ function ที่ใช้สำหรับสร้างด่าน Shop
- void setGroundShop() คือ function ที่ใช้สำหรับสร้างพื้นของด่าน Shop
- void buy(int) คือ function ที่ใช้สำหรับการซื้อไอเทมจากร้านค้า
- void stage2() คือ function ที่ใช้สำหรับสร้างด่าน 2
- void setGround2() คือ function ที่ใช้สำหรับสร้างพื้นของด่าน 2
- void setMonster2() คือ function ที่ใช้สำหรับสร้างหมีของด่าน 2
- void setFish2() คือ function ที่ใช้สำหรับสร้างปลาของด่าน 2
- void setChest2() คือ function ที่ใช้สำหรับสร้างหีบสมบัติของด่าน 2
- void stage2boss() คือ function ที่ใช้สำหรับสร้าง และกำหนดพื้นที่ สำหรับบอสด่าน 2
- void stage3() คือ function ที่ใช้สำหรับสร้างด่าน 3
- void setGround3() คือ function ที่ใช้สำหรับสร้างพื้นของด่าน 3
- void setMonster3() คือ function ที่ใช้สำหรับสร้างหมีของด่าน 3
- void setChest3() คือ function ที่ใช้สำหรับสร้างหีบสมบัติของด่าน 3
- void stage3boss() คือ function ที่ใช้สำหรับสร้าง และกำหนดพื้นที่ สำหรับบอสด่าน 3
- void saveData() คือ function ที่ใช้สำหรับตั้งชื่อ และบันทึกข้อมูลลง Leaderboard.txt
- void loadSound() คือ function ที่ใช้สำหรับโหลดเสียงมาเก็บในตัวแปรต่างๆ

โปรเจคนี้เป็นส่วนหนึ่งของวิชา Programming Fundamental ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง
