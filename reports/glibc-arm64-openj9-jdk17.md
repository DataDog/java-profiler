---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 15:22:37 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1794341769 38
1794341774 38
1794341779 38
1794341784 38
1794341789 38
1794341794 38
1794341799 38
1794341804 38
1794341809 38
1794341814 38
1794341819 38
1794341824 38
1794341829 43
1794341834 43
1794341839 43
1794341844 48
1794341849 48
1794341854 48
1794341859 48
1794341864 47
```
</details>

---

