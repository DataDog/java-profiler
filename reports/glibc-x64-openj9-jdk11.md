---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 12:21:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 62-94 cores)</summary>

```
1794331001 94
1794331006 94
1794331011 77
1794331016 77
1794331021 77
1794331026 77
1794331031 77
1794331036 77
1794331041 77
1794331046 77
1794331051 79
1794331056 79
1794331061 79
1794331066 79
1794331071 79
1794331076 62
1794331081 62
1794331086 62
1794331091 62
1794331096 62
```
</details>

---

