---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 10:47:50 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (4 unique values: 48-54 cores)</summary>

```
1791988858 54
1791988863 54
1791988868 54
1791988873 54
1791988878 54
1791988883 54
1791988888 54
1791988893 54
1791988898 54
1791988903 54
1791988908 54
1791988913 54
1791988918 54
1791988923 54
1791988928 54
1791988933 54
1791988938 52
1791988943 52
1791988948 50
1791988953 50
```
</details>

---

