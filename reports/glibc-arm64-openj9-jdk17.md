---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:46:37 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 10 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 44-51 cores)</summary>

```
1792672896 44
1792672901 44
1792672906 44
1792672911 51
1792672916 51
1792672921 51
1792672926 51
1792672931 51
1792672936 51
1792672941 51
1792672946 51
1792672951 51
1792672956 51
1792672961 49
1792672966 49
1792672971 47
1792672976 47
1792672981 47
1792672986 47
1792672991 47
```
</details>

---

