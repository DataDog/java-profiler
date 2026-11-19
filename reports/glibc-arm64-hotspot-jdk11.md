---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1795112546 30
1795112551 30
1795112556 30
1795112561 30
1795112566 30
1795112571 30
1795112576 30
1795112581 30
1795112586 30
1795112591 30
1795112596 30
1795112601 30
1795112606 30
1795112611 30
1795112616 30
1795112621 30
1795112626 30
1795112631 30
1795112636 30
1795112641 30
```
</details>

---

