---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1795440788 31
1795440793 31
1795440798 33
1795440803 33
1795440808 33
1795440813 33
1795440818 33
1795440823 33
1795440828 33
1795440833 33
1795440838 33
1795440843 33
1795440848 33
1795440853 33
1795440858 33
1795440863 33
1795440868 33
1795440873 33
1795440878 33
1795440883 33
```
</details>

---

