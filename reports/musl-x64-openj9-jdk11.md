---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 07:33:16 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 8 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 56-79 cores)</summary>

```
1787311664 56
1787311669 56
1787311674 56
1787311679 56
1787311684 56
1787311690 56
1787311695 56
1787311700 56
1787311705 56
1787311710 56
1787311715 76
1787311720 76
1787311725 74
1787311730 74
1787311735 74
1787311740 74
1787311745 74
1787311750 79
1787311755 79
1787311760 79
```
</details>

---

