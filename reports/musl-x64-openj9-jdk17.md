---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-06 09:00:00 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (6 unique values: 48-80 cores)</summary>

```
1786020934 52
1786020939 52
1786020944 52
1786020949 52
1786020954 52
1786020959 52
1786020964 52
1786020969 52
1786020974 52
1786020979 52
1786020984 50
1786020989 50
1786020994 48
1786020999 48
1786021004 50
1786021009 50
1786021014 76
1786021019 76
1786021024 78
1786021029 78
```
</details>

---

