---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 07:14:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 49-70 cores)</summary>

```
1793880505 49
1793880510 49
1793880515 49
1793880520 49
1793880525 49
1793880530 49
1793880535 49
1793880540 49
1793880545 49
1793880550 49
1793880555 70
1793880560 70
1793880565 53
1793880570 53
1793880575 53
1793880580 53
1793880585 53
1793880590 53
1793880595 53
1793880600 53
```
</details>

---

