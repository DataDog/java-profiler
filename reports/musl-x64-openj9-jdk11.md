---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:33:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (5 unique values: 34-48 cores)</summary>

```
1786455000 39
1786455005 39
1786455010 39
1786455015 39
1786455020 39
1786455025 39
1786455030 39
1786455035 39
1786455040 39
1786455045 39
1786455050 48
1786455055 48
1786455060 48
1786455065 48
1786455070 38
1786455075 38
1786455080 38
1786455085 38
1786455090 38
1786455095 38
```
</details>

---

