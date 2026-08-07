---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 12:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 33-45 cores)</summary>

```
1786119612 43
1786119617 43
1786119622 43
1786119627 43
1786119632 43
1786119637 43
1786119642 45
1786119648 45
1786119653 45
1786119658 45
1786119663 45
1786119668 45
1786119673 45
1786119678 45
1786119683 33
1786119688 33
1786119693 33
1786119698 33
1786119703 33
1786119708 33
```
</details>

---

