---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-13 03:09:24 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 6 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770969988 24
1770969993 24
1770969998 24
1770970003 24
1770970008 24
1770970013 24
1770970018 24
1770970023 24
1770970028 24
1770970033 24
1770970038 24
1770970043 24
1770970048 24
1770970053 24
1770970058 24
1770970063 24
1770970068 24
1770970073 24
1770970078 24
1770970083 24
```
</details>

---

