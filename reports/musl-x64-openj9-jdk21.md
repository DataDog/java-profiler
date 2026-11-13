---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:46:24 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794580864 80
1794580869 80
1794580874 80
1794580879 80
1794580884 82
1794580889 82
1794580894 82
1794580899 82
1794580904 82
1794580909 82
1794580914 82
1794580919 82
1794580924 82
1794580929 82
1794580934 82
1794580939 82
1794580944 82
1794580949 82
1794580954 82
1794580959 82
```
</details>

---

