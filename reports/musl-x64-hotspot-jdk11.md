---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 16:29:17 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 23-27 cores)</summary>

```
1777321165 23
1777321170 23
1777321175 23
1777321180 23
1777321185 23
1777321190 23
1777321195 23
1777321200 27
1777321205 27
1777321210 27
1777321215 27
1777321220 27
1777321225 27
1777321230 27
1777321235 27
1777321240 27
1777321245 27
1777321250 23
1777321255 23
1777321260 23
```
</details>

---

