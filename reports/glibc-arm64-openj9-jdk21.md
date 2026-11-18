---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:25:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 9 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 15 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1795015315 38
1795015320 38
1795015325 38
1795015330 38
1795015335 38
1795015340 38
1795015345 38
1795015350 38
1795015355 38
1795015360 38
1795015365 38
1795015370 38
1795015375 38
1795015380 38
1795015385 38
1795015390 38
1795015395 38
1795015401 51
1795015406 51
1795015411 51
```
</details>

---

