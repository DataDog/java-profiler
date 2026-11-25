---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:15:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 13 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795604994 33
1795604999 33
1795605004 28
1795605009 28
1795605014 28
1795605019 28
1795605024 28
1795605029 28
1795605034 28
1795605039 28
1795605044 28
1795605049 28
1795605054 28
1795605059 28
1795605064 28
1795605069 28
1795605074 28
1795605079 28
1795605084 33
1795605089 33
```
</details>

---

