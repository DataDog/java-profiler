---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 12:29:05 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 10 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 42-54 cores)</summary>

```
1792513445 42
1792513450 42
1792513455 42
1792513460 42
1792513465 42
1792513470 42
1792513475 42
1792513480 42
1792513485 42
1792513490 42
1792513495 42
1792513500 42
1792513505 42
1792513510 42
1792513515 42
1792513520 42
1792513525 54
1792513530 54
1792513535 54
1792513540 54
```
</details>

---

