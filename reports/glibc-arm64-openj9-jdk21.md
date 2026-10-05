---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 00:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 13 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791175943 51
1791175948 64
1791175953 64
1791175958 64
1791175963 64
1791175968 64
1791175973 64
1791175978 64
1791175983 64
1791175988 64
1791175993 64
1791175998 64
1791176003 64
1791176008 64
1791176014 64
1791176019 64
1791176024 64
1791176029 64
1791176034 64
1791176039 64
```
</details>

---

