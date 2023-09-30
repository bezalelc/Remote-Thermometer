import './style/Home.css'
import ProbComponent from "./ProbComponent";

const Home = () => {

    return (
        <div className="home-container probs-data-container">
            <ProbComponent probId={"prob1"} />
            <ProbComponent probId={"prob2"} />
            <ProbComponent probId={"prob3"} />
            <ProbComponent probId={"prob4"} />
        </div>
    );
}

export default Home;