---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-17 13:29:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 41-49 cores)</summary>

```
1794939933 49
1794939938 49
1794939943 44
1794939948 44
1794939953 44
1794939958 44
1794939964 44
1794939969 44
1794939974 46
1794939979 46
1794939984 46
1794939989 46
1794939994 46
1794939999 41
1794940004 41
1794940009 41
1794940014 41
1794940019 41
1794940024 41
1794940029 41
```
</details>

---

