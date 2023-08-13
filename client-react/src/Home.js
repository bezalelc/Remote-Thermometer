import { useState, useEffect } from "react";
import { ref, onValue } from "firebase/database";
import { useFirebase } from "./FirebaseContext";
import ProbsList from './ProbsList'
import './style/Home.css'

const Home = () => {
    const { firebaseDB, userId } = useFirebase()
    const [data, setData] = useState({})
    const dbRef = ref(firebaseDB, '/UsersData/' + userId)


    useEffect(() => {
        onValue(dbRef, (snapshot) => {
            setData(data => ({
                ...data,
                ...snapshot.val()
            }))
        })
    }, [userId])

    return (
        <div className="home-container">
            <ProbsList probsData={data} />
        </div>
    );
}

export default Home;