---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 16:05:39 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 32-51 cores)</summary>

```
1793739673 32
1793739678 32
1793739683 32
1793739688 32
1793739693 32
1793739698 49
1793739703 49
1793739708 49
1793739713 49
1793739718 49
1793739723 49
1793739728 49
1793739733 49
1793739738 49
1793739743 49
1793739748 49
1793739753 49
1793739758 49
1793739763 49
1793739768 51
```
</details>

---

