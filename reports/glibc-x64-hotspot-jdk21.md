---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-12 08:15:37 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 59-63 cores)</summary>

```
1770901515 63
1770901520 63
1770901525 63
1770901530 63
1770901535 59
1770901540 59
1770901545 59
1770901550 59
1770901555 59
1770901560 59
1770901565 59
1770901570 59
1770901575 59
1770901580 59
1770901585 59
1770901590 59
1770901595 59
1770901600 59
1770901605 59
1770901610 59
```
</details>

---

