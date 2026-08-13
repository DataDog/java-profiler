---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 16:44:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 14 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1786653551 64
1786653556 64
1786653561 64
1786653566 44
1786653571 44
1786653576 44
1786653581 44
1786653586 44
1786653591 44
1786653596 44
1786653601 44
1786653606 44
1786653611 44
1786653616 44
1786653621 44
1786653626 44
1786653631 44
1786653636 44
1786653641 44
1786653646 44
```
</details>

---

