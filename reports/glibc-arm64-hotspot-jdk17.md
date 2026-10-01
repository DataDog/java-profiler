---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:40:04 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1790854478 40
1790854483 40
1790854488 40
1790854493 40
1790854498 40
1790854503 40
1790854508 40
1790854513 40
1790854518 40
1790854523 40
1790854528 40
1790854533 40
1790854538 40
1790854543 40
1790854548 40
1790854553 40
1790854558 40
1790854563 35
1790854568 35
1790854573 35
```
</details>

---

