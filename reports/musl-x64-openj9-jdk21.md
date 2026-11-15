---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 18:26:30 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
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
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1794784896 91
1794784901 91
1794784906 91
1794784911 91
1794784916 91
1794784921 91
1794784926 91
1794784931 91
1794784936 91
1794784941 91
1794784946 91
1794784951 96
1794784956 96
1794784961 96
1794784966 96
1794784971 96
1794784976 96
1794784981 96
1794784986 96
1794784991 96
```
</details>

---

