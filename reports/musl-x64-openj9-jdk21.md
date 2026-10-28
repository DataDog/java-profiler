---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:48:57 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1793187851 79
1793187856 79
1793187861 79
1793187866 79
1793187871 79
1793187876 79
1793187881 79
1793187886 79
1793187891 74
1793187896 74
1793187901 74
1793187906 74
1793187911 74
1793187916 74
1793187921 76
1793187926 76
1793187931 76
1793187936 76
1793187941 76
1793187946 76
```
</details>

---

