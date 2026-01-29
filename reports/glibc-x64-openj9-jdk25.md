---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 06:14:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 502 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 21.43/sec |
| Health Score | 1339% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1769684919 32
1769684924 32
1769684929 32
1769684934 32
1769684939 32
1769684944 32
1769684949 32
1769684954 32
1769684959 32
1769684964 32
1769684969 32
1769684974 32
1769684979 32
1769684984 32
1769684989 32
1769684994 32
1769684999 32
1769685004 32
1769685009 32
1769685014 32
```
</details>

---

