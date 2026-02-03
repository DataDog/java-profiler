---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 07:41:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 50-62 cores)</summary>

```
1770122101 52
1770122106 52
1770122111 52
1770122116 52
1770122121 52
1770122126 52
1770122131 52
1770122136 52
1770122141 52
1770122146 52
1770122151 50
1770122156 50
1770122161 62
1770122166 62
1770122171 62
1770122176 62
1770122181 61
1770122186 61
1770122191 61
1770122196 61
```
</details>

---

