---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:34:14 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 79-85 cores)</summary>

```
1794850164 85
1794850169 85
1794850174 85
1794850179 84
1794850184 84
1794850189 81
1794850194 81
1794850199 79
1794850204 79
1794850209 79
1794850214 79
1794850219 79
1794850224 79
1794850229 79
1794850234 82
1794850239 82
1794850244 82
1794850249 82
1794850254 82
1794850259 82
```
</details>

---

