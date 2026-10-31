---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 21:17:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 14-48 cores)</summary>

```
1793409249 14
1793409254 14
1793409259 14
1793409264 14
1793409269 14
1793409274 48
1793409279 48
1793409284 48
1793409289 48
1793409294 35
1793409299 35
1793409304 35
1793409309 35
1793409314 35
1793409319 35
1793409324 35
1793409329 35
1793409334 35
1793409339 35
1793409344 35
```
</details>

---

