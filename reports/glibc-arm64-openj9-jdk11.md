---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 06:57:15 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1104 |
| Sample Rate | 18.40/sec |
| Health Score | 1150% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793012009 46
1793012014 46
1793012019 46
1793012024 46
1793012029 46
1793012034 46
1793012039 46
1793012044 46
1793012049 51
1793012054 51
1793012059 51
1793012064 51
1793012069 51
1793012074 51
1793012079 51
1793012084 51
1793012089 51
1793012094 51
1793012099 51
1793012104 51
```
</details>

---

