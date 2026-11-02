---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793656928 51
1793656933 51
1793656938 51
1793656943 51
1793656948 51
1793656953 51
1793656958 51
1793656963 51
1793656968 51
1793656973 51
1793656978 51
1793656983 51
1793656988 51
1793656993 51
1793656998 51
1793657003 51
1793657008 51
1793657013 51
1793657018 51
1793657023 51
```
</details>

---

