---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 15:28:25 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 10 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1787080924 14
1787080929 14
1787080934 14
1787080939 14
1787080944 14
1787080949 14
1787080954 14
1787080959 14
1787080964 14
1787080969 14
1787080974 14
1787080979 14
1787080984 14
1787080989 14
1787080994 14
1787080999 14
1787081004 14
1787081009 14
1787081014 34
1787081019 34
```
</details>

---

