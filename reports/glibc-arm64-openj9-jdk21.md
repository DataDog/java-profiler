---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 15 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 46-59 cores)</summary>

```
1793830783 46
1793830788 46
1793830793 46
1793830798 46
1793830803 46
1793830808 46
1793830813 46
1793830818 46
1793830823 59
1793830828 59
1793830833 59
1793830838 59
1793830843 59
1793830848 59
1793830853 46
1793830858 46
1793830863 46
1793830868 46
1793830873 46
1793830878 46
```
</details>

---

