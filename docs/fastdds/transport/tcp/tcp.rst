.. _transport_tcp_tcp:

TCP Transport
=============

TCP is a connection oriented transport, so the :ref:`dds_layer_domainParticipant` must establish a TCP connection
to the remote peer before sending data messages.
Therefore, one of the communicating DomainParticipants (the one acting
as *server*) must open a TCP port listening for incoming connections, and the other one (the one acting as *client*)
must connect to this port.

.. note::

  The *server* and *client* concepts are independent from the DDS concepts of
  :ref:`dds_layer_publisher`, :ref:`dds_layer_subscriber`,
  :ref:`dds_layer_publisher_dataWriter`, and :ref:`dds_layer_subscriber_dataReader`.
  Any of them can act as a *TCP Server* or *TCP Client* when establishing the connection,
  and the DDS communication will work over this connection.

.. warning::

   This documentation assumes the reader has basic knowledge of TCP/IP concepts, since terms like
   Time To Live (TTL), Cyclic Redundancy Check (CRC), Transport Layer Security (TLS),
   socket buffers, and port numbering are not explained in detail.
   However, it is possible to configure a basic TCP transport on *Fast DDS* without this knowledge.


.. _transport_tcp_transportDescriptor:

TCPTransportDescriptor
----------------------

*eProsima Fast DDS* implements TCP transport for both TCPv4 and TCPv6.
Each of these transports is independent from the other, and has its own :class:`TransportDescriptor`.
However, they share many of their features, and most of the :class:`TransportDescriptor` data members are common.

The following table describes the common data members for both TCPv4 and TCPv6.

.. |InterfaceWhitelist| replace:: :ref:`whitelist-interfaces`
.. |TLSconfig| replace:: :ref:`transport_tcp_tls`

+------------------------------+----------------------+---------+------------------------------------------------------+
| Member                       | Data type            | Default | Description                                          |
+==============================+======================+=========+======================================================+
| ``sendBufferSize``           | ``uint32_t``         | ``0``   | Size of the sending buffer of the socket (octets).   |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``receiveBufferSize``        | ``uint32_t``         | ``0``   | Size of the receiving buffer of the socket (octets). |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``interfaceWhiteList``       | ``vector<string>``   | empty   | List of allowed interfaces.                          |
|                              |                      |         | See |InterfaceWhitelist|                             |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``TTL``                      | ``uint8_t``          | ``1``   | Time to live, in number of hops.                     |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``listening_ports``          | ``vector<uint16_t>`` | empty   | List of ports to listen as *server*.                 |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``keep_alive_frequency_ms``  | ``uint32_t``         | 5000    | Frequency of RTCP keep alive requests (in ms).       |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``keep_alive_timeout_ms``    | ``uint32_t``         | 15000   | Time since sending the last keep alive request to    |
|                              |                      |         | consider a connection as broken (in ms).             |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``max_logical_port``         | ``uint16_t``         | 100     | Maximum number of logical ports to try               |
|                              |                      |         | during RTCP negotiation.                             |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``logical_port_range``       | ``uint16_t``         | 20      | Maximum number of logical ports per request to try   |
|                              |                      |         | during RTCP negotiation.                             |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``logical_port_increment``   | ``uint16_t``         | 2       | Increment between logical ports to try               |
|                              |                      |         | during RTCP negotiation.                             |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``enable_tcp_nodelay``       | ``bool``             | false   | Enables the TCP_NODELAY socket option.               |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``calculate_crc``            | ``bool``             | true    | True to calculate and send CRC on message headers.   |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``check_crc``                | ``bool``             | true    | True to check the CRC of incoming message headers.   |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``apply_security``           | ``bool``             | false   | True to use TLS. See |TLSconfig|.                    |
+------------------------------+----------------------+---------+------------------------------------------------------+
| ``tls_config``               | ``TLSConfig``        |         | Configuration for TLS. See |TLSconfig|.              |
+------------------------------+----------------------+---------+------------------------------------------------------+

.. note::

  If ``listening_ports`` is left empty, the participant will not be able to receive incoming connections but will be able
  to connect to other participants that have configured their listening ports.

.. _transport_tcp_v4transportDescriptor:

TCPv4TransportDescriptor
^^^^^^^^^^^^^^^^^^^^^^^^

The following table describes the data members that are exclusive for :class:`TCPv4TransportDescriptor`.

.. |WANconfig| replace:: :ref:`transport_tcp_wan`

+------------------------------+----------------------+---------+------------------------------------------------------+
| Member                       | Data type            | Default | Description                                          |
+==============================+======================+=========+======================================================+
| ``wan_addr``                 | ``octet[4]``         | empty   | Configuration for TLS. See |WANconfig|.              |
+------------------------------+----------------------+---------+------------------------------------------------------+

.. note::

   The *kind* value for a TCPv4TransportDescriptor is given by the value
   ``eprosima::fastrtps::rtps::LOCATOR_KIND_TCPv4``


.. _transport_tcp_v6transportDescriptor:

TCPv6TransportDescriptor
^^^^^^^^^^^^^^^^^^^^^^^^

:class:`TCPv6TransportDescriptor` has no additional data members from the common ones described in
:ref:`transport_tcp_transportDescriptor`.

.. note::

   The *kind* value for a TCPv6TransportDescriptor is given by the value
   ``eprosima::fastrtps::rtps::LOCATOR_KIND_TCPv6``

.. _transport_tcp_enabling:

Enabling TCP Transport
----------------------

To enable TCP transport in a DomainParticipant, you need to
create an instance of :ref:`transport_tcp_v4transportDescriptor` (for TCPv4) or
:ref:`transport_tcp_v6transportDescriptor` (for TCPv6), and add it to the user transport list of the
DomainParticipant.

If you provide ``listening_ports`` on the descriptor, the DomainParticipant will act
as *TCP server*, listening for incoming remote connections on the given ports.
The examples below show this procedure in both C++ code and XML file.

+---------------------------------------------------------+
| **C++**                                                 |
+---------------------------------------------------------+
| .. literalinclude:: /../code/DDSCodeTester.cpp          |
|    :language: c++                                       |
|    :start-after: //CONF-TCP-TRANSPORT-SETTING-SERVER    |
|    :end-before: //!--                                   |
|    :dedent: 8                                           |
+---------------------------------------------------------+
| **XML**                                                 |
+---------------------------------------------------------+
| .. literalinclude:: /../code/XMLTester.xml              |
|    :language: xml                                       |
|    :start-after: <!-->CONF-TCP-TRANSPORT-SETTING-SERVER |
|    :end-before: <!--><-->                               |
|    :lines: 2-3,5-                                       |
|    :append: </profiles>                                 |
+---------------------------------------------------------+

If you provide ``initialPeersList`` to the DomainParticipant, it will act
as *TCP client*, trying to connect to the remote *servers* at the given addresses and ports.
The examples below show this procedure in both C++ code and XML file.
See :ref:`Simple Initial Peers` for more information about their configuration.

+----------------------------------------------------------+
| **C++**                                                  |
+----------------------------------------------------------+
| .. literalinclude:: /../code/DDSCodeTester.cpp           |
|    :language: c++                                        |
|    :start-after: //CONF-TCP-TRANSPORT-SETTING-CLIENT     |
|    :end-before: //!--                                    |
|    :dedent: 8                                            |
+----------------------------------------------------------+
| **XML**                                                  |
+----------------------------------------------------------+
| .. literalinclude:: /../code/XMLTester.xml               |
|    :language: xml                                        |
|    :start-after: <!-->CONF-TCP-TRANSPORT-SETTING-CLIENT  |
|    :end-before: <!--><-->                                |
|    :lines: 2-3,5-                                        |
|    :append: </profiles>                                  |
+----------------------------------------------------------+

:ref:`transport_tcp_example` shows how to use and configure a TCP transport.


.. _transport_tcp_wan:

WAN or Internet Communication over TCPv4
----------------------------------------

*Fast DDS* is able to connect through the Internet or other WAN networks when configured properly.
To achieve this kind of scenarios, the involved network devices such as routers and firewalls
must add the rules to allow the communication.

For example, imagine we have the scenario represented on the following figure:

.. image:: /01-figures/TCP_WAN.png
    :align: center

* A DomainParticipant acts as a *TCP server* listening on port ``5100``
  and is connected to the WAN through a router with public IP ``80.80.99.45``.

* Another DomainParticipant acts as a *TCP client* and has configured
  the server's IP address and port in its ``initial_peer`` list.

On the server side, the router must be configured to forward to the *TCP server*
all traffic incoming to port ``5100``. Typically, a NAT routing of port ``5100`` to our
machine is enough. Any existing firewall should be configured as well.

In addition, to allow incoming connections through a WAN,
the :ref:`transport_tcp_v4transportDescriptor` must indicate its **public** IP address
in the ``wan_addr`` data member. The following examples show how to configure
the DomainParticipant both in C++ and XML.

+---------------------------------------------------------+
| **C++**                                                 |
+---------------------------------------------------------+
| .. literalinclude:: /../code/DDSCodeTester.cpp          |
|    :language: c++                                       |
|    :start-after: //CONF-TCP-TRANSPORT-SETTING-SERVER    |
|    :end-before: //!--                                   |
|    :dedent: 8                                           |
+---------------------------------------------------------+
| **XML**                                                 |
+---------------------------------------------------------+
| .. literalinclude:: /../code/XMLTester.xml              |
|    :language: xml                                       |
|    :start-after: <!-->CONF-TCP-TRANSPORT-SETTING-SERVER |
|    :end-before: <!--><-->                               |
|    :lines: 2-3,5-                                       |
|    :append: </profiles>                                 |
+---------------------------------------------------------+

On the client side, the DomainParticipant must be configured
with the **public** IP address and ``listening_port`` of the *TCP server* as
``initial_peer``.

+----------------------------------------------------------+
| **C++**                                                  |
+----------------------------------------------------------+
| .. literalinclude:: /../code/DDSCodeTester.cpp           |
|    :language: c++                                        |
|    :start-after: //CONF-TCP-TRANSPORT-SETTING-CLIENT     |
|    :end-before: //!--                                    |
|    :dedent: 8                                            |
+----------------------------------------------------------+
| **XML**                                                  |
+----------------------------------------------------------+
| .. literalinclude:: /../code/XMLTester.xml               |
|    :language: xml                                        |
|    :start-after: <!-->CONF-TCP-TRANSPORT-SETTING-CLIENT  |
|    :end-before: <!--><-->                                |
|    :lines: 2-3,5-                                        |
|    :append: </profiles>                                  |
+----------------------------------------------------------+


.. _transport_tcp_example:

HelloWorldExampleTCP
--------------------

A TCP version of helloworld example can be found in the ``examples/C++/DDS/HelloWorldExampleTCP`` folder.
It shows a publisher and a subscriber that communicate through TCP.
The publisher is configured as *TCP server* while the Subscriber is acting as *TCP client*.



