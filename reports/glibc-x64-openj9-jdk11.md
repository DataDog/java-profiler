---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 07:41:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (5 unique values: 22-45 cores)</summary>

```
1770122081 34
1770122086 34
1770122091 34
1770122096 34
1770122101 34
1770122106 34
1770122111 34
1770122116 34
1770122121 36
1770122126 36
1770122131 40
1770122136 40
1770122141 40
1770122146 40
1770122151 45
1770122156 45
1770122161 45
1770122166 22
1770122171 22
1770122176 22
```
</details>

---

