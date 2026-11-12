---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 12 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794495928 55
1794495933 53
1794495938 53
1794495943 53
1794495948 53
1794495953 53
1794495958 53
1794495963 53
1794495968 53
1794495973 53
1794495978 53
1794495983 53
1794495988 53
1794495993 53
1794495999 53
1794496004 53
1794496009 53
1794496014 53
1794496019 53
1794496024 53
```
</details>

---

