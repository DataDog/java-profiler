---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 16:58:40 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792615961 64
1792615966 64
1792615971 64
1792615976 64
1792615981 64
1792615986 64
1792615991 64
1792615996 64
1792616001 64
1792616006 64
1792616011 64
1792616016 64
1792616021 64
1792616026 64
1792616031 64
1792616036 64
1792616041 64
1792616046 64
1792616051 64
1792616056 64
```
</details>

---

