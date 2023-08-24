import { useState } from "react";
import './style/Home.css'
import ProbComponent from "./ProbComponent";

const Home = () => {
    const [itemIdFocus, setItemIdFocus] = useState(null)

    return (
        <div className="home-container probs-data-container">
            <ProbComponent probId={"prob1"} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
            <ProbComponent probId={"prob2"} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
            <ProbComponent probId={"prob3"} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
            <ProbComponent probId={"prob4"} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
        </div>
    );
}

export default Home;