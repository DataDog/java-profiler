---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 10:08:54 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791986624 48
1791986629 48
1791986634 48
1791986639 43
1791986644 43
1791986649 43
1791986654 43
1791986659 43
1791986664 43
1791986669 43
1791986674 43
1791986679 43
1791986684 43
1791986689 38
1791986694 38
1791986699 38
1791986704 38
1791986709 38
1791986714 38
1791986719 43
```
</details>

---

