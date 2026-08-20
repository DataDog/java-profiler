---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 82-90 cores)</summary>

```
1787232416 90
1787232421 90
1787232426 90
1787232431 90
1787232436 90
1787232441 90
1787232446 90
1787232451 90
1787232456 90
1787232461 90
1787232466 90
1787232471 90
1787232476 88
1787232481 88
1787232487 88
1787232492 88
1787232497 88
1787232502 88
1787232507 88
1787232512 88
```
</details>

---

