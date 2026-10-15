---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-15 07:15:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 9-32 cores)</summary>

```
1792062653 9
1792062658 9
1792062663 9
1792062668 9
1792062674 9
1792062679 9
1792062684 9
1792062689 9
1792062694 9
1792062699 9
1792062704 9
1792062709 9
1792062714 9
1792062719 9
1792062724 9
1792062729 9
1792062734 32
1792062739 32
1792062744 32
1792062749 32
```
</details>

---

