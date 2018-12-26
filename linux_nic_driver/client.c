struct _net_cart_t {
    int fd;
    unsigned char mac_address[6];
}

void* nc_open(const char* dev_name) {
    if (!dev_name)
        return nullptr;
    _net_cart_t *nc = new _net_cart_t;
    memset(nc->mac_address, 0, 6);

    char name[265];
    sprintf(name, "/dev/%s", dev_name);
    nc->fd = open(name, O_RDWR);
    if (nc->fd < 0) {
        delete nc;
        printf("cannot open [%s]\n", dev_name);
        return nullptr;
    }
    return nc;
}

void nc_close(void* handle) {
    if (!handle)
        return;
    _net_card_t *nc = (_net_card_t *)handle;
    close(nc->fd);
    ///
    delete nc;
}

int nc_read(void *handle, char *buf, int len, int tmo_sec) {
    _net_card_t *nc = (_net_card_t *)handle;
    if (!nc) return -1;
    while (true) {
        fd_set rdst;
        FD_ZERO(&rdst);
        FD_SET(nc->fd, &rdst);
        struct timeval timeout;
        timeout.tv_sec = tmo_sec;
        timeout.tv_usec = 0;
        int status = select(nc->fd + 1, &rdst, NULL, NULL, tmo_sec != 0 ? &timeout : NULL);
        if (status < 0) return -1;
        if (status == 0) return 0;

        int ret = read(nc->fd, buf, len);
        if (ret < 14) { //小于以太网或者出错
            if (ret < 0) return -1;
            return 0;
        }
        if (nc_filter_read_data(buf, ret) == 0) {
            return ret;
        }
    }
    return 0;
}

int nc_write(void *handle, char *buf, int len, int tmo_sec) {
    _net_card_t *nc = (_net_card_t *)handle;
    if (!nc) return -1;
    return write(nc->fd, buf, len);
}