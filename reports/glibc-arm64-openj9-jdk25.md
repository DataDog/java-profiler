---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 00:57:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790744050 43
1790744055 43
1790744060 43
1790744065 43
1790744070 43
1790744075 43
1790744080 43
1790744085 43
1790744090 43
1790744095 43
1790744100 43
1790744105 43
1790744110 43
1790744115 43
1790744120 43
1790744125 48
1790744130 48
1790744135 48
1790744140 48
1790744145 48
```
</details>

---

