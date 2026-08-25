---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:54:18 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1787672939 34
1787672944 34
1787672949 34
1787672954 34
1787672959 34
1787672964 34
1787672969 34
1787672974 34
1787672979 29
1787672984 29
1787672989 29
1787672994 29
1787672999 29
1787673004 29
1787673009 29
1787673014 29
1787673019 29
1787673024 29
1787673029 29
1787673034 24
```
</details>

---

