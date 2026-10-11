---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-11 01:02:46 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 56-66 cores)</summary>

```
1791694723 56
1791694728 58
1791694733 58
1791694738 58
1791694743 56
1791694748 56
1791694753 56
1791694758 56
1791694763 56
1791694768 56
1791694773 56
1791694778 56
1791694783 58
1791694788 58
1791694793 58
1791694798 58
1791694803 58
1791694808 58
1791694813 58
1791694818 58
```
</details>

---

