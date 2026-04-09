---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-09 05:04:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1775724969 38
1775724974 38
1775724979 38
1775724984 38
1775724989 43
1775724994 43
1775724999 43
1775725004 43
1775725009 43
1775725014 43
1775725019 43
1775725024 43
1775725029 43
1775725034 43
1775725039 43
1775725044 43
1775725049 43
1775725054 43
1775725059 43
1775725064 43
```
</details>

---

