---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-29 10:11:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 53-76 cores)</summary>

```
1777471592 76
1777471597 76
1777471602 76
1777471607 76
1777471612 76
1777471617 76
1777471622 76
1777471627 74
1777471632 74
1777471637 74
1777471642 76
1777471647 76
1777471652 53
1777471657 53
1777471662 53
1777471667 53
1777471672 53
1777471677 53
1777471682 53
1777471687 53
```
</details>

---

