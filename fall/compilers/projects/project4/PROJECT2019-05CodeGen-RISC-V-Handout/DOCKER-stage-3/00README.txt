Date: 2019.10.10

06CODEGEN-RISCV/DOCKER-stage-3/00README.


        根據老師說的，我建好一個docker image，並上傳到dockerhub
(網址：https://hub.docker.com/r/qooqoo/riscv_qemu  )。
進入這個docker image產生的continer就 不需要 再做額外設定(例如: apt-get install vim、cp .....等)。而學生可以直接把這image pull下來，然後執行，便能直接使用riscv tool和qemu。pull下來的時間很短。
 
       附件為修改後的如何用docker建置riscv 環境的說明檔之word file (只改變B和C兩大點)。
 
--
