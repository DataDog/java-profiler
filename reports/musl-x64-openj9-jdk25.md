---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:40:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 52-75 cores)</summary>

```
1790854477 52
1790854482 52
1790854487 70
1790854492 70
1790854497 70
1790854502 70
1790854507 70
1790854512 70
1790854517 70
1790854522 73
1790854527 73
1790854532 75
1790854537 75
1790854542 75
1790854547 75
1790854552 75
1790854557 75
1790854562 75
1790854567 75
1790854572 75
```
</details>

---

