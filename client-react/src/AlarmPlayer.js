import React, { useEffect, useState, useRef } from 'react';
import './style/AlarmPlayer.css'

const AlarmPlayer = ({ probId, currentVal, destVal }) => {
    const [alarmWait, setAlarmWait] = useState(false)
    const [snooze, setSnooze] = useState(false)
    const [isPlayingNow, setIsPlayingNow] = useState(false)
    const temperaturAlarmSoundRef = useRef(new Audio('./resources/sound/sound-alert-in-hall.wav'))

    useEffect(() => {
        if (alarmWait && currentVal >= destVal) {
            temperaturAlarmSoundRef.current.play()
            setIsPlayingNow(true)

            temperaturAlarmSoundRef.current.onended = () => {
                setIsPlayingNow(false)
                if (alarmWait) {
                    setTimeout(() => {
                        temperaturAlarmSoundRef.current.play()
                        setIsPlayingNow(true)
                    }, 5000); // 5 * 1000 = 5 sec in milliseconds
                }
            };
        } else {
            temperaturAlarmSoundRef.current.pause()
            temperaturAlarmSoundRef.current.currentTime = 0
            setIsPlayingNow(false)
        }
    }, [alarmWait, currentVal, destVal])

    const setStopHandler = () => {
        if (snooze) {
            setSnooze(false)
            setAlarmWait(false)
        }
        else {
            setAlarmWait(!alarmWait)
        }
    }

    const snoozeHandler = () => {
        setAlarmWait(false);
        setSnooze(true)

        // Set a timeout for snooze duration (e.g., 5 minutes)
        setTimeout(() => {
            if (snooze) {
                setAlarmWait(true);
            }
        }, 60000); // 60 * 1000= 1 minutes in milliseconds
    }


    return (
        <div className={`alarm-player ${isPlayingNow ? 'alarm-player-blinking' : ''}`}>
            <button onClick={setStopHandler} className='alarm-player-start'>{alarmWait || snooze ? "Stop Alarm" : "Set Alarm"}</button>
            {isPlayingNow && <button onClick={snoozeHandler} className={`alarm - player - snooze ${isPlayingNow ? 'alarm-player-snooze-with-margin' : ''} `}>Snooze</button>}
        </div>
    );
};

export default AlarmPlayer;
