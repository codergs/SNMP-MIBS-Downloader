// Author: This code snippet is from Ben Rockwood's net-snmp programming guide
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string.h>
int main(int argc, char ** argv)
{
        struct snmp_session session;
        struct snmp_session *sess_handle;
        struct snmp_pdu *pdu;
        struct snmp_pdu *response;
        struct variable_list *vars;
        oid id_oid[MAX_OID_LEN];
        oid serial_oid[MAX_OID_LEN];
        size_t id_len = MAX_OID_LEN;
        size_t serial_len = MAX_OID_LEN;
        int status;
        struct tree * mib_tree;
        /*********************/
        if(argv[1] == NULL){
        printf("Please supply a hostname\n");
                exit(1);
        }
        init_snmp("Main check");
        snmp_sess_init( &session );
        session.version = SNMP_VERSION_1;
        session.community = "public";
        session.community_len = strlen(session.community);
        session.peername = argv[1];
        sess_handle = snmp_open(&session);
        add_mibdir(".");
        mib_tree = read_mib("mibs/SNMPv2-MIB.txt");
        pdu = snmp_pdu_create(SNMP_MSG_GET);
        read_objid("SNMPv2-MIB::sysDescr.0", id_oid, &id_len);
        snmp_add_null_var(pdu, id_oid, id_len);
        read_objid("SNMPv2-MIB::sysObjectID.0", serial_oid, &serial_len);
        snmp_add_null_var(pdu, serial_oid, serial_len);
        status = snmp_synch_response(sess_handle, pdu, &response);
        for(vars = response->variables; vars; vars = vars->next_variable)
        print_value(vars->name, vars->name_length, vars);
        snmp_free_pdu(response);
        snmp_close(sess_handle);
        return (0);
}

 
