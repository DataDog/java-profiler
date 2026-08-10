---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 09:13:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 10 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (4 unique values: 11-29 cores)</summary>

```
1786367358 11
1786367363 11
1786367368 11
1786367373 23
1786367378 23
1786367383 23
1786367388 23
1786367393 23
1786367398 23
1786367403 23
1786367408 23
1786367413 23
1786367418 23
1786367423 23
1786367428 23
1786367433 23
1786367438 23
1786367443 23
1786367448 23
1786367453 24
```
</details>

---

