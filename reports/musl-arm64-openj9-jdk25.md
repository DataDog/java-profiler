---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 16:21:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 14 |
| Allocations | 175 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794950083 64
1794950088 64
1794950093 64
1794950098 51
1794950103 51
1794950108 51
1794950113 51
1794950118 51
1794950123 51
1794950128 51
1794950133 51
1794950138 51
1794950143 51
1794950148 51
1794950153 51
1794950158 51
1794950163 51
1794950168 51
1794950173 51
1794950178 51
```
</details>

---

