---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 11:26:16 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1792163985 24
1792163990 24
1792163995 24
1792164000 24
1792164005 24
1792164010 24
1792164015 24
1792164020 24
1792164025 24
1792164030 24
1792164035 24
1792164040 24
1792164045 24
1792164050 24
1792164055 24
1792164060 24
1792164065 24
1792164070 24
1792164075 24
1792164080 32
```
</details>

---

