---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 55-84 cores)</summary>

```
1793880486 82
1793880491 82
1793880496 82
1793880501 82
1793880506 82
1793880512 82
1793880517 82
1793880522 82
1793880527 84
1793880532 84
1793880537 84
1793880542 64
1793880547 64
1793880552 64
1793880557 64
1793880562 64
1793880567 64
1793880572 64
1793880577 64
1793880582 64
```
</details>

---

