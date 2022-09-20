
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS patient_information (
    uuid                varchar (256) PRIMARY KEY UNIQUE ,  -- 唯一标识
    name                varchar (256) NOT NULL ,            -- 姓名
    idn                 varchar (256) NOT NULL UNIQUE ,     -- 身份证号码
    birth               int NOT NULL ,            -- 出生年月日 YYYYMMDD
    gender              int NOT NULL ,                      -- 性别
    ethnic              varchar (256) NOT NULL ,            -- 民族
    address             varchar (256) NOT NULL ,            -- 身份证户籍地址
    address1            varchar (256) NULL ,                -- 常住地址
    phone               varchar (256) NOT NULL ,            -- 本人手机/电话
    phone1              varchar (256) NULL ,                -- 亲属电话/紧急联系人
    create_time         varchar (256) NOT NULL ,            -- 创建时间
    update_time         varchar (256) NOT NULL ,            -- 修改时间
    is_delete           boolean default false               -- 是否被删除
);

-- INSERT INTO patient_information
-- (uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time) VALUES
-- (uuid_generate_v4(), '张三', '32331009112w', '20000327', 1, '汉', '江苏海安人民路', '', '13073226555', '',localtimestamp(2), localtimestamp(2))
-- returning uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time;

-- SELECT * FROM patient_information WHERE is_delete=false LIMIT :limit OFFSET :offset;

-- UPDATE patient_information SET is_delete = true, update_time = current_timestamp(2) WHERE uuid=:info RETURNING *;

-- SELECT * FROM patient_information WHERE name like :'%name%' and is_delete=false;

-- SELECT uuid, name, idn, birth, gender, ethnic, address, address1, phone, phone1, create_time, update_time FROM patient_information WHERE is_delete=false LIMIT :limit OFFSET :offset;
SELECT * FROM patient_information WHERE name like '%李%' AND is_delete=false LIMIT 5;