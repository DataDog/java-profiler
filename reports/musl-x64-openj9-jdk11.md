---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-13 09:58:41 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1062 |
| Sample Rate | 17.70/sec |
| Health Score | 1106% |
| Threads | 12 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (5 unique values: 72-81 cores)</summary>

```
1778680425 72
1778680430 72
1778680435 72
1778680440 72
1778680445 75
1778680450 75
1778680455 75
1778680460 75
1778680465 75
1778680470 75
1778680475 75
1778680480 75
1778680485 75
1778680490 79
1778680495 79
1778680500 79
1778680505 79
1778680510 79
1778680515 77
1778680520 77
```
</details>

---

