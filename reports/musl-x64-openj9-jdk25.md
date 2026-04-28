---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 10:05:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 21-30 cores)</summary>

```
1777384743 30
1777384748 30
1777384753 30
1777384758 30
1777384763 30
1777384768 30
1777384773 30
1777384778 30
1777384783 25
1777384788 25
1777384793 25
1777384798 25
1777384803 25
1777384808 25
1777384813 30
1777384818 30
1777384823 28
1777384828 28
1777384833 28
1777384838 28
```
</details>

---

