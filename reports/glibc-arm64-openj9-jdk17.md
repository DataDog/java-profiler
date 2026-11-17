---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 13:29:09 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 41-49 cores)</summary>

```
1794939935 49
1794939940 49
1794939945 44
1794939950 44
1794939955 44
1794939960 44
1794939965 44
1794939970 44
1794939975 46
1794939980 46
1794939985 46
1794939990 46
1794939995 46
1794940000 41
1794940005 41
1794940010 41
1794940015 41
1794940020 41
1794940025 41
1794940030 41
```
</details>

---

