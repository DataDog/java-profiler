---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-10 19:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1775863625 68
1775863630 68
1775863635 68
1775863640 68
1775863645 68
1775863650 68
1775863655 68
1775863660 68
1775863665 68
1775863670 68
1775863675 68
1775863680 68
1775863685 68
1775863690 68
1775863695 68
1775863700 68
1775863705 68
1775863710 64
1775863715 64
1775863720 64
```
</details>

---

