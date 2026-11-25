---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795618909 31
1795618914 31
1795618919 31
1795618924 31
1795618929 36
1795618934 36
1795618939 36
1795618944 36
1795618949 36
1795618954 36
1795618959 36
1795618964 36
1795618969 36
1795618974 36
1795618979 36
1795618984 36
1795618989 36
1795618994 36
1795618999 36
1795619004 36
```
</details>

---

