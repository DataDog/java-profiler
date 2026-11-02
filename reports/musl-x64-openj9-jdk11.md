---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 17:11:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793656888 51
1793656893 49
1793656898 49
1793656903 49
1793656908 49
1793656913 49
1793656918 49
1793656923 49
1793656928 49
1793656933 49
1793656938 49
1793656943 49
1793656948 49
1793656953 49
1793656958 49
1793656963 49
1793656968 49
1793656973 49
1793656978 49
1793656983 49
```
</details>

---

