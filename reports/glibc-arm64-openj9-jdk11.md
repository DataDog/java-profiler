---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 09:57:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 13 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794235964 32
1794235969 32
1794235974 32
1794235979 32
1794235984 32
1794235989 32
1794235994 32
1794235999 32
1794236004 32
1794236009 32
1794236014 32
1794236019 32
1794236024 32
1794236029 32
1794236034 32
1794236039 32
1794236044 32
1794236049 32
1794236054 32
1794236059 32
```
</details>

---

