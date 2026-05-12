---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:53:32 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 81-85 cores)</summary>

```
1778582836 81
1778582841 81
1778582846 81
1778582851 81
1778582856 84
1778582861 84
1778582866 82
1778582871 82
1778582876 82
1778582881 82
1778582886 82
1778582891 83
1778582896 83
1778582901 83
1778582906 83
1778582911 83
1778582916 83
1778582921 83
1778582926 83
1778582931 83
```
</details>

---

