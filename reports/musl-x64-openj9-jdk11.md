---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 20.93/sec |
| Health Score | 1308% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 27.30/sec |
| Health Score | 1706% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1769526941 28
1769526946 28
1769526951 28
1769526956 28
1769526961 28
1769526966 28
1769526971 28
1769526976 28
1769526981 28
1769526986 28
1769526991 30
1769526996 30
1769527001 30
1769527006 30
1769527011 30
1769527016 30
1769527021 30
1769527026 30
1769527031 30
1769527036 30
```
</details>

---

