---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 13:04:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1794852041 59
1794852046 64
1794852051 64
1794852056 64
1794852061 64
1794852066 64
1794852071 64
1794852076 64
1794852081 64
1794852086 51
1794852091 51
1794852096 51
1794852101 51
1794852106 51
1794852111 51
1794852116 51
1794852121 51
1794852126 51
1794852131 51
1794852136 51
```
</details>

---

