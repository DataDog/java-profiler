---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 10:29:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 69-77 cores)</summary>

```
1791382964 69
1791382969 69
1791382974 69
1791382979 69
1791382984 69
1791382989 77
1791382994 77
1791382999 77
1791383004 77
1791383009 77
1791383014 77
1791383019 77
1791383024 77
1791383029 77
1791383034 77
1791383039 77
1791383044 77
1791383049 77
1791383054 77
1791383059 77
```
</details>

---

