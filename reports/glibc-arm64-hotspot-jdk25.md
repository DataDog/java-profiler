---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 13:07:01 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787072549 64
1787072554 64
1787072559 64
1787072564 64
1787072569 64
1787072574 64
1787072579 64
1787072584 64
1787072589 64
1787072594 64
1787072599 64
1787072604 64
1787072609 64
1787072614 64
1787072619 64
1787072624 64
1787072629 64
1787072634 64
1787072639 64
1787072644 64
```
</details>

---

