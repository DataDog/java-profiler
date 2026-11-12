---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 14:47:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1794512564 26
1794512569 26
1794512574 26
1794512579 26
1794512584 26
1794512589 26
1794512594 26
1794512599 26
1794512604 26
1794512609 26
1794512614 28
1794512619 28
1794512624 28
1794512629 28
1794512634 26
1794512639 26
1794512644 26
1794512649 26
1794512654 26
1794512659 26
```
</details>

---

