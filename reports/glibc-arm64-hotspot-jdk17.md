---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:55:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 11 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792403407 43
1792403412 43
1792403417 43
1792403422 43
1792403427 43
1792403432 43
1792403437 43
1792403442 43
1792403447 43
1792403452 43
1792403457 43
1792403462 43
1792403467 43
1792403472 43
1792403477 43
1792403482 48
1792403487 48
1792403492 48
1792403497 48
1792403502 48
```
</details>

---

