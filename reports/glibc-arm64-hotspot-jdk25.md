---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 08:57:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793019216 48
1793019221 48
1793019226 48
1793019231 48
1793019236 48
1793019241 48
1793019246 48
1793019251 48
1793019256 36
1793019261 36
1793019266 36
1793019271 36
1793019276 36
1793019281 36
1793019286 36
1793019291 36
1793019296 36
1793019301 36
1793019306 36
1793019311 36
```
</details>

---

