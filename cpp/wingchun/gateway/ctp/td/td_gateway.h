//
// Created by qlu on 2019/1/14.
//

#ifndef WC_2_TD_GATEWAY_H
#define WC_2_TD_GATEWAY_H

#include "ThostFtdcTraderApi.h"
#include "order_mapper.h"
#include "gateway/impl/gateway_impl.h"

namespace kungfu
{
    namespace ctp
    {
        class TdGateway: public CThostFtdcTraderSpi, public TdGatewayImpl
        {
        public:
            TdGateway(const std::string& front_uri, const std::string& broker_id, const std::string& account_id, const std::string& password, int log_level):
                    TdGatewayImpl(SOURCE_CTP, TD_GATEWAY_NAME(SOURCE_CTP, account_id), log_level), front_uri_(front_uri), broker_id_(broker_id), account_id_(account_id), password_(password), front_id_(-1), session_id_(-1), order_ref_(-1), request_id_(0) {}
            ~TdGateway() {};

            virtual void init();
            virtual void start();

            virtual const std::string& get_account_id() const { return account_id_; }
            virtual const AccountType get_account_type() const { return AccountTypeFuture; }

            virtual bool insert_order(const OrderInput& input);
            virtual bool cancel_order(const OrderAction& action);
            virtual bool req_position();
            virtual bool req_position_detail();
            virtual bool req_account();

            virtual void OnFrontConnected();
            virtual void OnFrontDisconnected(int nReason);
            virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
            virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);
            virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

        private:
            std::string front_uri_;
            std::string broker_id_;
            std::string account_id_;
            std::string password_;

            int front_id_;
            int session_id_;

            int order_ref_;
            int request_id_;

            CThostFtdcTraderApi* api_;
            std::shared_ptr<kungfu::ctp::OrderMapper> order_mapper_;

            static const std::unordered_map<int, std::string> kDisconnectedReasonMap;

            bool login();
            bool req_settlement_confirm();
            bool req_qry_instrument();
        };
    }
}
#endif //WC_2_TD_GATEWAY_H
