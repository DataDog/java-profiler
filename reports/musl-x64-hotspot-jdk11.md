---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 07:41:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 74-91 cores)</summary>

```
1770122096 91
1770122101 91
1770122106 74
1770122111 74
1770122116 74
1770122121 74
1770122126 74
1770122131 74
1770122136 74
1770122141 74
1770122146 74
1770122151 74
1770122156 74
1770122161 74
1770122166 74
1770122171 74
1770122176 74
1770122181 74
1770122186 74
1770122191 74
```
</details>

---

