---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 18:25:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1792707665 61
1792707670 61
1792707675 61
1792707680 63
1792707685 63
1792707690 63
1792707695 63
1792707700 63
1792707705 63
1792707710 63
1792707715 63
1792707720 63
1792707725 63
1792707730 63
1792707735 63
1792707740 63
1792707745 63
1792707750 63
1792707755 63
1792707760 63
```
</details>

---

