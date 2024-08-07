1. io 多路复用   socket   fd   epoll   read write error  status

eventloop acceptor  channel socket socketutil  eventloopthread eventloopthreadpool 

2. buffer recv send cache  

bufferring<T> rtppacket rtmppacket

3. protocol  parse 

rtpheader payload  aac-adts h264 startcode-nalu

4. rtsp rtp rtcp  / rtmp  / http 


5. parse rtp ... inputrtp  

6. demuxer  sort rtp to audio video

7. decoder audio aac g771a video h264 h265

8. render 

9. encoder  h264 h265 video aac g711a audio

10. muxer

11. video audio to rtp

12. send rtp





******************************************************************************************************************

1. io 多路复用