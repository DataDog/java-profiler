---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:33:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1795011966 77
1795011971 77
1795011976 77
1795011981 77
1795011986 77
1795011991 77
1795011996 79
1795012001 79
1795012006 79
1795012011 79
1795012016 79
1795012021 79
1795012026 79
1795012031 79
1795012036 79
1795012041 79
1795012046 79
1795012051 79
1795012056 79
1795012061 79
```
</details>

---

