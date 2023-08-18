import { useEffect } from "react";

const ProbSummery = ({ probData, probKey, itemIdFocus, setItemIdFocus }) => {

    const convertMillisToTime = (startTime, currentTime) => {
        const seconds = Math.floor((parseInt(currentTime) - parseInt(startTime)) / 1000);
        if (!seconds) {
            return '0'
        }
        const hours = Math.floor(seconds / 3600).toString().padStart(2, '0')
        const minutes = Math.floor((seconds % 3600) / 60).toString().padStart(2, '0')
        const remainingSeconds = (seconds % 60).toString().padStart(2, '0')

        return `${hours}:${minutes}:${remainingSeconds}`;
    };

    // useEffect(() => {
    //     if (probData.temperature >= probData.destTemperature) {
    //         const audio = new Audio('/ring.mp3')
    //         // console.log(audio)
    //         audio.play();
    //     }
    // }, [probData])


    return (
        <div className="prob-data-summery" onClick={() => setItemIdFocus(itemIdFocus === probKey ? null : probKey)}>
            <div className="prob-list-title">Prob {probKey.match(/\d+/)[0]}</div>
            <div className="prob-data-deg-container" >
                <div className="home-temperature-container" >
                    <span className="temperature">{parseFloat(probData.temperature).toFixed(2)}</span>
                    <span className="temperature-sing">&deg;</span>
                    <span className="home-temperature-c">C</span>
                </div>
                <div className="home-dest-temperature-container" >
                    <span className="temperature-separetor">/&nbsp;</span>
                    <span className="dest-temperature">{parseInt(probData.destTemperature)}</span>
                    <span className="temperature-sing">&deg;</span>
                    <span className="home-dest-temperature-c">C</span>
                </div>
            </div>
            <div className="prob-data-time-container">
                {convertMillisToTime(probData.startTime, probData.currentTime)}
            </div>
        </div>
    );
}

export default ProbSummery;