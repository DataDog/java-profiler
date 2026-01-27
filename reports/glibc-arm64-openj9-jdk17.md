---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-01-27 09:51:03 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 9 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 4 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769524972 24
1769524977 24
1769524982 24
1769524987 24
1769524992 24
1769524997 24
1769525002 24
1769525007 24
1769525012 24
1769525017 24
1769525022 24
1769525027 24
1769525032 24
1769525037 24
1769525042 24
1769525047 24
1769525052 24
1769525057 24
1769525062 24
1769525067 24
```
</details>

---

