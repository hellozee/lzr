#pragma once

namespace lzr{
    class laser{
    private:
        unsigned int m_power;
        bool m_emitting;
        //a timer
        
    public:
        laser()
        {
            m_emitting = false;
            m_power = 1;
        }
        
        void 
        set_power(unsigned int power)
        {
            //power should be between 1-100
            m_power = power > 100 ? 100 : power < 1 ? 1 : power;
        }
        
        int 
        power()
        {
            return m_power;
        }
        
        void 
        keep_alive()
        {
            //reset the timer
        }
        
        /* lzr::laser::start_emission starts emission if the laser is not emitting.
         * Returns a bool to determine whether there was error or not.
         * Using std::optional seems a good idea here.
         */
        bool 
        start_emission()
        {
            if(!m_emitting){
                m_emitting = true;
                return false;
            }
            return true;
        }
        
        /* Exact opposite of lzr::laser::start_emission
         */
        bool 
        stop_emission()
        {
            if(m_emitting){
                m_emitting = false;
                return false;
            }
            return true;
        }
        
        bool 
        is_emitting()
        {
            return m_emitting;
        }

    };
}
