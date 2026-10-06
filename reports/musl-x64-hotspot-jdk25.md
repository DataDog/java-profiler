---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 10:08:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 78-86 cores)</summary>

```
1791295372 80
1791295377 80
1791295382 80
1791295387 78
1791295392 78
1791295397 78
1791295402 78
1791295407 78
1791295412 78
1791295417 78
1791295422 78
1791295427 84
1791295432 84
1791295437 84
1791295442 86
1791295447 86
1791295452 84
1791295457 84
1791295462 84
1791295467 84
```
</details>

---

