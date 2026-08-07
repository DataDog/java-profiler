---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1786119556 49
1786119561 51
1786119566 51
1786119571 51
1786119576 51
1786119581 51
1786119586 51
1786119591 49
1786119596 49
1786119601 49
1786119606 49
1786119612 49
1786119617 49
1786119622 49
1786119627 49
1786119632 49
1786119637 49
1786119642 49
1786119647 49
1786119652 49
```
</details>

---

