---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 76-86 cores)</summary>

```
1791470933 86
1791470938 86
1791470943 86
1791470948 86
1791470953 78
1791470958 78
1791470963 78
1791470968 78
1791470973 78
1791470978 78
1791470983 78
1791470988 78
1791470993 78
1791470998 78
1791471003 78
1791471008 78
1791471013 78
1791471018 78
1791471023 78
1791471028 76
```
</details>

---

