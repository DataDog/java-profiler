---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 00:53:01 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792385397 48
1792385402 48
1792385407 48
1792385412 48
1792385417 48
1792385422 48
1792385427 48
1792385432 48
1792385437 48
1792385442 48
1792385447 48
1792385452 48
1792385457 48
1792385462 48
1792385467 48
1792385472 48
1792385477 43
1792385482 43
1792385487 38
1792385492 38
```
</details>

---

