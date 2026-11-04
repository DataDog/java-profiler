---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 15:01:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1793822226 74
1793822231 74
1793822236 74
1793822241 74
1793822246 76
1793822251 76
1793822256 76
1793822261 76
1793822266 76
1793822271 76
1793822276 76
1793822281 76
1793822286 76
1793822291 76
1793822296 81
1793822301 81
1793822306 81
1793822311 81
1793822316 81
1793822321 81
```
</details>

---

