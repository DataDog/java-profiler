---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-21 00:02:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
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
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 28-47 cores)</summary>

```
1795237114 28
1795237119 28
1795237124 28
1795237129 28
1795237134 45
1795237139 45
1795237144 28
1795237149 28
1795237154 28
1795237159 28
1795237164 28
1795237169 28
1795237174 30
1795237179 30
1795237184 28
1795237189 28
1795237194 28
1795237199 28
1795237204 28
1795237209 45
```
</details>

---

