/************************************************************************
 *
 * Copyright (c) 2010
 * PrismTech Ltd.
 * All rights Reserved.
 *
 * LOGICAL_NAME:    MSFPPacketListener.cpp
 * FUNCTION:        .
 * MODULE:          .
 * DATE             August 2010.
 ************************************************************************
 *
 * This file contains the implementation of MSFPPacketListener
 *
 ***/

#include "opensplice_dds/MSFPPacket_listener.h"
#include "opensplice_dds/check_status.h"
#include <sstream>

using namespace DDS;

namespace micros_swarm_framework{

    void MSFPPacketListener::on_data_available(DDS::DataReader_ptr reader)
      THROW_ORB_EXCEPTIONS
    {
        
        DDS::ReturnCode_t status;
        MSFPPacketSeq packetSeq;
        SampleInfoSeq infoSeq;

        status = MSFPPacketDR_->take(packetSeq, infoSeq, LENGTH_UNLIMITED,
        ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        //checkStatus(status, "MSFPPacketDataReader::read");

        for (CORBA::ULong i = 0; i < packetSeq.length(); i++)
        {
            (*callBack_)(packetSeq[i]);
        }
        status = MSFPPacketDR_->return_loan(packetSeq, infoSeq);
        checkStatus(status, "MSFPPacketDataReader::return_loan");
        
        // unblock the waitset in Subscriber main loop
        //guardCond_->set_trigger_value(true);
    };

    void MSFPPacketListener::on_requested_deadline_missed(DDS::DataReader_ptr
      reader, const DDS::RequestedDeadlineMissedStatus &status)THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_requested_deadline_missed] : triggered\n");
        printf("\n=== [MSFPPacketListener::on_requested_deadline_missed] : stopping\n");
        //closed_ = true;
        // unblock the waitset in Subscriber main loop
        //guardCond_->set_trigger_value(true);
    };

    void MSFPPacketListener::on_requested_incompatible_qos(DDS::DataReader_ptr
      reader, const DDS::RequestedIncompatibleQosStatus &status)
      THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_requested_incompatible_qos] : triggered\n");
    };

    void MSFPPacketListener::on_sample_rejected(DDS::DataReader_ptr reader, const
      DDS::SampleRejectedStatus &status)THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_sample_rejected] : triggered\n");
    };

    void MSFPPacketListener::on_liveliness_changed(DDS::DataReader_ptr reader,
      const DDS::LivelinessChangedStatus &status)THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_liveliness_changed] : triggered\n");
    };

    void MSFPPacketListener::on_subscription_matched(DDS::DataReader_ptr reader,
      const DDS::SubscriptionMatchedStatus &status)THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_subscription_matched] : triggered\n");
    };

    void MSFPPacketListener::on_sample_lost(DDS::DataReader_ptr reader, const DDS
      ::SampleLostStatus &status)THROW_ORB_EXCEPTIONS
    {
        printf("\n=== [MSFPPacketListener::on_sample_lost] : triggered\n");
    };
};
