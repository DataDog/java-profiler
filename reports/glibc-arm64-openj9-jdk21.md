---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 13:02:40 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 12 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 13 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790787406 43
1790787411 43
1790787416 43
1790787421 43
1790787426 43
1790787431 43
1790787436 43
1790787441 48
1790787447 48
1790787452 48
1790787457 48
1790787462 48
1790787467 48
1790787472 48
1790787477 48
1790787482 48
1790787487 48
1790787492 48
1790787497 48
1790787502 48
```
</details>

---

