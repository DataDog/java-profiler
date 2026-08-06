---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-06 08:59:58 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 10 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 18-23 cores)</summary>

```
1786020944 23
1786020949 18
1786020954 18
1786020959 18
1786020964 18
1786020969 18
1786020974 18
1786020979 18
1786020984 18
1786020989 23
1786020994 23
1786020999 23
1786021004 23
1786021009 23
1786021014 23
1786021019 23
1786021024 23
1786021029 23
1786021034 23
1786021039 23
```
</details>

---

