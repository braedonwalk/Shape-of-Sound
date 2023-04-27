midiSphere = "/midi:sphere_bluetooth:1/control_change"
midiOcta = "/midi:octa_bluetooth:1/control_change"
midiCube = "/midi:cube_bluetooth:1/control_change"

noteArray = [
  [:C3, :D3, :Ef3, :G3],
  [:C3, :D3, :Ef3],
  [:C3, :D3, :F3],
  [:C3, :G3],
  [:C3, :Ef3, :G3],
  [:C3, :Ef3, :F3, :G3],
  [:C3, :F3, :G3],
  [:C3, :Ef3],
  [:C3, :D3, :Ef3, :F3, :G3],
  [:C3, :F3]
]

use_real_time

#MID VOICE
with_fx :reverb do
  with_fx :level, amp: 0, amp_slide: 5 do |level|
    with_fx :pan do |pan|
      live_loop :melody do
        cc, value = sync midiSphere
        puts cc
        
        if cc == 1 #Y
          cc, p = sync midiSphere
          
          control level, amp: 1
          
          inputRange = [0.0, 100.0]
          maxPan = [-1, 1.0]
          p = rMap(inputRange, maxPan, p)
          
          puts "Pan #{p}"
          control pan, pan: p
        end
        
        if cc == 2 #Z
          value = value / 10
          n = (value % 10)
          puts "Array Index: #{n}"
          
          use_transpose 5
          use_synth :hollow
          play noteArray[n].tick
        end
        
        if cc == 7
          value = value / 10
          n = (value % 10)
          puts "Array Index: #{n}"
          
          use_synth :hollow
          play noteArray[n].tick
          control level, amp: 0
        end
        
        sleep 0.125
        
      end
      
    end
  end
end

#HIGH VOICE
with_fx :reverb do
  ##| maxAmp = 0.5
  with_fx :level, amp: 0 do |level|
    with_fx :flanger, amp: 0 do |flange|
      
      use_synth :hollow
      play :Ef4, sustain: 60 * 60 * 10
      play :Bb4, sustain: 60 * 60 * 10
      
      live_loop :highVoice do
        cc, value = sync midiOcta
        ##| puts "High Value: #{value}"
        
        inputRange = [0.0, 100.0]
        maxRange = [0.1, 1.0]
        vol = rMap(inputRange, maxRange, value)
        
        
        if cc == 1
          control level, amp: vol
          control flange, amp: vol
          ##| s = play :Ef4, amp: 1, amp_slide: 1, amp_slide_shape: 7
          
          ##| control s, amp: 0
        end
        
        if cc == 7
          control level, amp: 0
        end
        
        inputRange = [0.0, 100.0]
        maxVal = [0.125, 0.25]
        val = rMap(inputRange, maxVal, value)
        
        ##| play :C4
        ##| play :F4
        ##| sleep val
        
      end
    end
  end
end

#BASS
with_fx :reverb do
  with_fx :level, amp: 0, amp_slide: 5 do |level|
    use_synth :hollow
    my_note = play :C1, sustain: 60 * 60 * 10
    
    live_loop :bass do
      cc, value = sync midiCube
      
      if cc == 1
        puts 1
        control level, amp: 1
        control my_note, note: :C2
      end
      if cc == 2
        puts 2
        control level, amp: 0.6
        control my_note, note: :G1
      end
      if cc == 3
        puts 3
        control level, amp: 1
        control my_note, note: :F1
      end
      if cc == 4
        puts 4
        control level, amp: 1
        control my_note, note: :Ef1
      end
      if cc == 5
        puts 5
        control level, amp: 0.8
        control my_note, note: :D1
      end
      if cc == 6
        puts 6
        control level, amp: 1.2
        control my_note, note: :C1
      end
      if cc == 7
        puts 7
        control level, amp: 0
      end
      
      sleep 0.25
    end
  end
end

with_fx :reverb, mix: 0.5 do
  live_loop :ocean do
    s = synth [:bnoise, :pnoise].choose, amp: 0.01,
      attack: rrand(0, 2), sustain: rrand(1, 2), release: rrand(2, 4)
    control s, pan: rrand(-1, 1)
    
    sleep [2, 4].choose
  end
end

define :rMap do |rIn, rOut, v|
  dOut = rOut[1] - rOut[0]
  dIn = rIn[1] - rIn[0]
  dOut / dIn * (v - rIn[0]) + rOut[0]
end
