---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 12:41:59 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789749377 40
1789749382 40
1789749387 40
1789749392 40
1789749397 40
1789749402 40
1789749407 40
1789749412 40
1789749417 40
1789749422 40
1789749427 40
1789749432 40
1789749437 40
1789749442 40
1789749447 40
1789749452 40
1789749457 40
1789749462 40
1789749467 40
1789749472 40
```
</details>

---

