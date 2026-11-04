---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:58:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1793789554 33
1793789559 33
1793789564 33
1793789569 33
1793789574 33
1793789579 33
1793789584 38
1793789589 38
1793789594 38
1793789599 38
1793789604 38
1793789609 40
1793789614 40
1793789619 40
1793789624 40
1793789629 40
1793789634 40
1793789639 40
1793789644 40
1793789649 40
```
</details>

---

