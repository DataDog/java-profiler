---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:14:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 44-45 cores)</summary>

```
1793880481 45
1793880486 45
1793880491 45
1793880496 45
1793880501 45
1793880506 45
1793880511 45
1793880516 45
1793880521 45
1793880526 45
1793880531 45
1793880536 45
1793880541 45
1793880546 45
1793880551 45
1793880556 45
1793880561 45
1793880566 45
1793880571 45
1793880576 44
```
</details>

---

