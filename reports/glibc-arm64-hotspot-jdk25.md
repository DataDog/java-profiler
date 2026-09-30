---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 11:36:49 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790782333 43
1790782338 43
1790782343 43
1790782348 43
1790782353 48
1790782358 48
1790782363 48
1790782368 48
1790782373 48
1790782378 48
1790782383 48
1790782388 48
1790782393 48
1790782398 48
1790782403 48
1790782408 48
1790782413 48
1790782418 48
1790782423 48
1790782428 48
```
</details>

---

