#include "job_bus.hpp"
#include "client.hpp"
#include "job_queue.hpp"

#include <ctime>
#include <iostream>
#include <vector>
#include <QThread>

bool JobBus::m_exit_loop = false;
JobBus* JobBus::m_instance = nullptr;

JobQueue JobBus::m_jobQ;
JobQueue JobBus::m_resQ;

JobBus::JobsMap JobBus::m_JobBus_map {

    {Job::LIST,             Client::contact_list},
    {Job::SEARCH,           Client::contact_search},
    {Job::ADD,              Client::contact_add_user},
    {Job::REMOVE,           Client::contact_remove_user},
    {Job::AVAILABLE,        Client::contact_available},
    {Job::SETUSER,          Client::user_set_username},
    {Job::SETPASS,          Client::user_set_password},
    {Job::CREATE,           Client::user_register_user},
    {Job::LOGIN,            Client::user_login}, 
    {Job::LOGGED,           Client::user_get_logged_in},
    {Job::GETUSER,          Client::user_get_username},
    {Job::DISP_CONTACTS,    Client::contact_get_contacts},
    {Job::CHAT,             Client::chat_get_all},
    {Job::SEND,             Client::chat_send},
    {Job::GETID,            Client::user_get_id},
    {Job::DELIVERED,        Client::chat_deliver},
    {Job::PENDING,          Client::chat_get_pending},
};

JobBus* JobBus::get_instance()
{
    if(!m_instance){
        m_instance = new JobBus();
        QObject::connect(m_instance, &JobBus::new_job, m_instance, &JobBus::handle);
    }

    return m_instance;
}

JobBus::~JobBus()
{
}

void JobBus::create(Job &&t_job){
    m_jobQ.push(t_job);
    emit JobBus::get_instance()->new_job();
}

void JobBus::create(Job &t_job){
    m_jobQ.push(t_job);
    emit JobBus::get_instance()->new_job();
}

void JobBus::handle() {
   
    Job job;

    if (false == m_jobQ.empty()) {      
        
        m_jobQ.pop_try(job);
        m_JobBus_map[job.m_command](job);

        if ( Job::DISCARD != job.m_command )
        {
            m_resQ.push(job);
            emit JobBus::get_instance()->job_ready();
        }
    }  
}

bool JobBus::get_response(Job &t_job){

    if (true == m_resQ.empty()){
        return false;
    }

    bool res = m_resQ.pop_try(t_job);

    if (false == res){
        return false;
    }

    return true;
} 

void JobBus::set_exit() { m_exit_loop = true; }
