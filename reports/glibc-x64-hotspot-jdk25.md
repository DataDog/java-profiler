---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:26:05 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 12 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 36-60 cores)</summary>

```
1773393624 60
1773393629 60
1773393634 60
1773393639 60
1773393644 60
1773393649 60
1773393654 60
1773393659 36
1773393664 36
1773393669 36
1773393674 36
1773393679 36
1773393684 36
1773393689 36
1773393694 36
1773393699 36
1773393704 36
1773393709 40
1773393714 40
1773393719 40
```
</details>

---

