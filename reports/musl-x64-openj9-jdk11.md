---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:49:56 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 65-71 cores)</summary>

```
1778150748 67
1778150753 67
1778150758 67
1778150763 67
1778150768 67
1778150773 67
1778150778 67
1778150783 65
1778150788 65
1778150793 65
1778150798 65
1778150803 65
1778150808 69
1778150813 69
1778150818 69
1778150823 69
1778150828 69
1778150833 71
1778150838 71
1778150843 71
```
</details>

---

