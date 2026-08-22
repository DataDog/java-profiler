---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 08:14:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787400579 79
1787400584 79
1787400589 79
1787400594 79
1787400599 81
1787400604 81
1787400609 79
1787400614 79
1787400619 79
1787400624 79
1787400629 79
1787400634 79
1787400639 79
1787400644 79
1787400649 79
1787400654 79
1787400659 79
1787400664 79
1787400669 79
1787400674 81
```
</details>

---

