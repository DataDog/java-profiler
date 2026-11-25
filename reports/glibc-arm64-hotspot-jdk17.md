---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:49:48 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 16 |
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
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 15-18 cores)</summary>

```
1795621546 17
1795621551 17
1795621556 15
1795621561 15
1795621566 15
1795621571 15
1795621576 16
1795621581 16
1795621586 16
1795621591 16
1795621596 16
1795621601 16
1795621606 16
1795621611 16
1795621616 16
1795621621 16
1795621626 18
1795621631 18
1795621636 16
1795621641 16
```
</details>

---

