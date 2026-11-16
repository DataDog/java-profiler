---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:18:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 63-67 cores)</summary>

```
1794823922 63
1794823927 63
1794823932 63
1794823937 63
1794823942 63
1794823947 63
1794823952 63
1794823957 63
1794823962 63
1794823967 63
1794823972 63
1794823977 63
1794823982 63
1794823987 63
1794823992 63
1794823997 63
1794824002 63
1794824007 63
1794824012 63
1794824017 63
```
</details>

---

