---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 16:34:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1777321764 59
1777321769 59
1777321774 59
1777321779 59
1777321784 59
1777321789 59
1777321794 47
1777321799 47
1777321804 64
1777321809 64
1777321814 64
1777321819 64
1777321824 64
1777321829 64
1777321834 64
1777321839 64
1777321844 64
1777321849 64
1777321854 64
1777321859 64
```
</details>

---

