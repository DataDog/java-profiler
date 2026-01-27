---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 30.70/sec |
| Health Score | 1919% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 62-71 cores)</summary>

```
1769524931 71
1769524936 71
1769524941 71
1769524946 71
1769524951 71
1769524956 71
1769524961 71
1769524966 69
1769524971 69
1769524976 67
1769524981 67
1769524986 67
1769524991 67
1769524996 69
1769525001 69
1769525006 69
1769525011 69
1769525016 69
1769525021 69
1769525026 69
```
</details>

---

