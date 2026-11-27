---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795793609 33
1795793614 33
1795793619 33
1795793624 33
1795793629 33
1795793634 33
1795793639 33
1795793644 33
1795793649 33
1795793654 33
1795793659 64
1795793664 64
1795793669 64
1795793674 64
1795793679 64
1795793684 64
1795793689 64
1795793694 64
1795793699 64
1795793704 64
```
</details>

---

