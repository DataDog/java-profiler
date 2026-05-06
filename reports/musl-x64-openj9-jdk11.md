---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 19:44:05 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 78-85 cores)</summary>

```
1778110800 78
1778110805 80
1778110810 80
1778110815 80
1778110820 80
1778110825 80
1778110830 80
1778110835 80
1778110840 80
1778110845 80
1778110850 80
1778110855 80
1778110860 80
1778110865 80
1778110870 85
1778110875 85
1778110880 85
1778110885 85
1778110890 81
1778110895 81
```
</details>

---

