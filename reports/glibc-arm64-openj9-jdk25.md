---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (3 unique values: 47-53 cores)</summary>

```
1791470918 48
1791470923 48
1791470928 48
1791470933 48
1791470938 48
1791470943 48
1791470948 48
1791470953 48
1791470958 48
1791470963 48
1791470968 48
1791470973 48
1791470978 48
1791470983 53
1791470988 53
1791470993 53
1791470998 47
1791471003 47
1791471008 47
1791471013 47
```
</details>

---

