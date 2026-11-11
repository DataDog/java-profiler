---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:36:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 34-46 cores)</summary>

```
1794396739 46
1794396744 46
1794396749 46
1794396754 34
1794396759 34
1794396764 34
1794396769 34
1794396774 39
1794396779 39
1794396784 39
1794396789 39
1794396794 39
1794396799 39
1794396804 39
1794396809 39
1794396814 39
1794396819 39
1794396824 39
1794396829 39
1794396834 39
```
</details>

---

