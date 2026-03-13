---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:26:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 11 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 13 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 50-53 cores)</summary>

```
1773393594 51
1773393599 51
1773393604 51
1773393609 53
1773393614 53
1773393619 53
1773393624 53
1773393629 53
1773393634 53
1773393639 53
1773393644 53
1773393649 53
1773393654 53
1773393659 50
1773393664 50
1773393669 50
1773393674 50
1773393679 50
1773393684 50
1773393689 50
```
</details>

---

