---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 08:40:35 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (7 unique values: 34-44 cores)</summary>

```
1789734956 35
1789734961 35
1789734966 35
1789734971 35
1789734976 38
1789734981 38
1789734986 38
1789734991 38
1789734996 38
1789735001 38
1789735006 43
1789735011 43
1789735016 43
1789735021 43
1789735026 43
1789735031 43
1789735036 43
1789735041 43
1789735046 41
1789735051 41
```
</details>

---

