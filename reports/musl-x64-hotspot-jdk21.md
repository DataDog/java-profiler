---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-13 07:10:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 12 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 67-87 cores)</summary>

```
1773399914 67
1773399919 67
1773399924 67
1773399929 67
1773399934 67
1773399939 83
1773399944 83
1773399949 83
1773399954 83
1773399959 83
1773399964 85
1773399969 85
1773399974 85
1773399979 85
1773399984 87
1773399989 87
1773399994 87
1773399999 87
1773400004 87
1773400009 87
```
</details>

---

