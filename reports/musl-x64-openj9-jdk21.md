---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:26:41 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 48-57 cores)</summary>

```
1795702917 48
1795702922 48
1795702927 48
1795702932 48
1795702937 48
1795702942 48
1795702947 55
1795702952 55
1795702957 55
1795702962 55
1795702967 55
1795702973 55
1795702978 57
1795702983 57
1795702988 55
1795702993 55
1795702998 55
1795703003 55
1795703008 55
1795703013 55
```
</details>

---

