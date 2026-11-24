---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 08:09:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1795525400 36
1795525405 36
1795525410 36
1795525415 36
1795525420 48
1795525425 48
1795525430 48
1795525435 48
1795525440 48
1795525445 48
1795525450 48
1795525455 48
1795525460 48
1795525465 48
1795525470 48
1795525475 48
1795525480 48
1795525485 48
1795525490 48
1795525495 48
```
</details>

---

