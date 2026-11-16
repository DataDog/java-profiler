---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 11:32:07 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 12 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 81-93 cores)</summary>

```
1794846441 93
1794846446 93
1794846451 89
1794846456 89
1794846461 89
1794846467 89
1794846472 89
1794846477 89
1794846482 89
1794846487 89
1794846492 89
1794846497 87
1794846502 87
1794846507 87
1794846512 87
1794846517 87
1794846522 87
1794846527 87
1794846532 83
1794846537 83
```
</details>

---

