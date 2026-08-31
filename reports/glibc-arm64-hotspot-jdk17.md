---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-31 06:39:02 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788172455 64
1788172460 64
1788172465 64
1788172470 64
1788172475 64
1788172480 64
1788172485 64
1788172490 64
1788172495 64
1788172500 64
1788172505 64
1788172510 64
1788172515 64
1788172520 64
1788172525 59
1788172530 59
1788172535 59
1788172540 59
1788172545 59
1788172550 59
```
</details>

---

