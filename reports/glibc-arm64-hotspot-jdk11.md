---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 13:18:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (3 unique values: 7-10 cores)</summary>

```
1792516407 8
1792516412 8
1792516417 8
1792516422 8
1792516427 8
1792516432 8
1792516437 8
1792516442 8
1792516447 8
1792516452 8
1792516457 8
1792516462 10
1792516467 10
1792516472 7
1792516477 7
1792516482 7
1792516487 7
1792516492 7
1792516497 7
1792516502 7
```
</details>

---

