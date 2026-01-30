---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-30 04:28:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 17.00/sec |
| Health Score | 1062% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 21.27/sec |
| Health Score | 1329% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769764879 30
1769764884 30
1769764889 30
1769764894 30
1769764899 30
1769764904 30
1769764909 30
1769764914 30
1769764919 30
1769764924 30
1769764929 30
1769764935 30
1769764940 30
1769764945 30
1769764950 30
1769764955 30
1769764960 30
1769764965 30
1769764970 30
1769764975 30
```
</details>

---

