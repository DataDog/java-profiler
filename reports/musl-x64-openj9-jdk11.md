---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 07:41:13 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 23-64 cores)</summary>

```
1770122086 64
1770122091 64
1770122096 64
1770122101 64
1770122106 23
1770122111 23
1770122116 23
1770122121 23
1770122126 23
1770122131 23
1770122136 23
1770122141 23
1770122146 23
1770122151 23
1770122156 23
1770122161 23
1770122166 23
1770122171 23
1770122176 23
1770122181 23
```
</details>

---

