---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:54:34 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1791470923 27
1791470928 27
1791470933 27
1791470938 27
1791470943 27
1791470948 27
1791470953 27
1791470958 27
1791470963 27
1791470968 27
1791470973 27
1791470978 27
1791470983 27
1791470988 27
1791470993 27
1791470998 27
1791471003 27
1791471008 25
1791471013 25
1791471018 25
```
</details>

---

