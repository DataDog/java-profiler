---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 06:59:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1794311781 28
1794311786 23
1794311791 23
1794311796 23
1794311801 23
1794311806 23
1794311811 23
1794311816 23
1794311821 23
1794311826 23
1794311831 23
1794311836 23
1794311841 23
1794311846 23
1794311851 23
1794311856 23
1794311861 23
1794311866 23
1794311871 23
1794311876 23
```
</details>

---

