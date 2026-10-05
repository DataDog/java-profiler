---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 35-51 cores)</summary>

```
1791193601 40
1791193606 40
1791193611 40
1791193616 40
1791193621 40
1791193626 40
1791193632 40
1791193637 40
1791193642 40
1791193647 40
1791193652 40
1791193657 40
1791193662 40
1791193667 40
1791193672 35
1791193677 35
1791193682 35
1791193687 35
1791193692 35
1791193697 35
```
</details>

---

