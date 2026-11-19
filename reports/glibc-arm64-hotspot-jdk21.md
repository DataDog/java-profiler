---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 46-50 cores)</summary>

```
1795112561 46
1795112566 46
1795112571 46
1795112576 46
1795112581 46
1795112586 46
1795112591 46
1795112596 46
1795112601 46
1795112606 48
1795112611 48
1795112616 48
1795112621 48
1795112626 48
1795112631 50
1795112636 50
1795112641 50
1795112646 50
1795112651 47
1795112656 47
```
</details>

---

