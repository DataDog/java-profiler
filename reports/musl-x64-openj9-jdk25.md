---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:28:01 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 23-26 cores)</summary>

```
1786454462 25
1786454467 25
1786454472 25
1786454477 25
1786454482 25
1786454487 25
1786454492 25
1786454497 25
1786454502 25
1786454507 25
1786454512 25
1786454517 25
1786454522 23
1786454527 23
1786454532 26
1786454537 26
1786454542 26
1786454547 26
1786454552 26
1786454557 26
```
</details>

---

