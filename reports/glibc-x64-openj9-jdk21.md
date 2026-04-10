---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-10 11:02:57 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 45-51 cores)</summary>

```
1775833051 47
1775833056 47
1775833061 47
1775833066 47
1775833071 51
1775833076 51
1775833081 51
1775833086 51
1775833091 51
1775833096 51
1775833101 51
1775833106 51
1775833111 45
1775833116 45
1775833121 45
1775833126 45
1775833131 45
1775833136 45
1775833141 45
1775833146 45
```
</details>

---

