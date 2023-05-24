//
// Created by fumedesk on 19.05.23.
//

#ifndef ANEZKASEARCH_POSTGRESSOURCE_H
#define ANEZKASEARCH_POSTGRESSOURCE_H

#include <optional>

#include <AppState.h>
#include <DataRow.h>
#include <pqxx/pqxx>

namespace anezkasearch {

template <typename IndT>
  requires ConcIndType<IndT>
class PostgresSource {
 public:
  PostgresSource(std::shared_ptr<AppState<IndT>> state) : m_state{state} {
    LOGI << "indexer source is postgres";
  }

  void Open() {
    std::string host =
        m_state->GetConfig()["indexer"]["host"].template as<std::string>();
    std::string user =
        m_state->GetConfig()["indexer"]["user"].template as<std::string>();
    std::string password =
        m_state->GetConfig()["indexer"]["password"].template as<std::string>();
    std::string port =
        m_state->GetConfig()["indexer"]["port"].template as<std::string>();
    std::string dbname =
        m_state->GetConfig()["indexer"]["dbname"].template as<std::string>();

    m_table = m_state->GetConfig()["indexer"]["content"]["table"]
                  .template as<std::string>();
    m_index_column = m_state->GetConfig()["indexer"]["content"]["index"]
                         .template as<std::string>();

    for (const auto& column :
         m_state->GetConfig()["indexer"]["content"]["key_columns"]) {
      m_text_column.push_back(column.template as<std::string>());
    }

    try {
      LOGI << "try open connection "
           << fmt::format("user={} host={} port={} dbname={}", user, host, port,
                          dbname);

      m_conn = std::make_unique<pqxx::connection>(
          fmt::format("user={} password={} host={} port={} dbname={}", user,
                      password, host, port, dbname));
      LOGI << "open connection successfully";
    } catch (const pqxx::sql_error& e) {
      LOGE << "postgres error: " << e.what();
      throw std::runtime_error("failed to open connection");
    } catch (const std::exception& e) {
      LOGE << "open connection error: " << e.what();
      throw std::runtime_error("failed to open connection");
    }
  }

  void Close() {
    m_conn.reset();
  }

  std::optional<DataRow<IndT>> Next() {
    std::stringstream squery;
    squery << "SELECT " << m_index_column << ", concat(";
    for (size_t i = 0; i < m_text_column.size() - 1; i++) {
      squery << m_text_column[i] << ", \' \', ";
    }
    squery << m_text_column[m_text_column.size() - 1] << ") ";
    squery << "FROM " << m_table << ";";

    pqxx::work tx{*m_conn};
    for (auto [id, text] : tx.query<IndT, std::string>(squery.str())) {
      LOGI << id << " " << text;
    }

    return std::nullopt;
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::unique_ptr<pqxx::connection> m_conn;
  std::string m_index_column;
  std::string m_table;
  std::vector<std::string> m_text_column;
  size_t m_row;
  size_t m_count_row;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_POSTGRESSOURCE_H
