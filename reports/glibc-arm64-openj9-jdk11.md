---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 17:11:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 8 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 12 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793656921 51
1793656926 51
1793656931 51
1793656936 51
1793656941 51
1793656946 51
1793656951 51
1793656956 51
1793656961 51
1793656966 51
1793656971 51
1793656976 51
1793656981 51
1793656986 51
1793656991 51
1793656996 51
1793657001 51
1793657006 51
1793657011 51
1793657016 51
```
</details>

---

