---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-06 09:00:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1786020949 70
1786020954 70
1786020959 72
1786020964 72
1786020969 72
1786020974 72
1786020979 72
1786020984 72
1786020989 72
1786020994 72
1786020999 72
1786021004 74
1786021009 74
1786021014 74
1786021019 74
1786021024 76
1786021029 76
1786021034 76
1786021039 76
1786021044 76
```
</details>

---

