---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786454961 51
1786454966 51
1786454971 51
1786454976 51
1786454981 51
1786454986 51
1786454991 51
1786454996 46
1786455001 46
1786455006 46
1786455011 46
1786455016 46
1786455021 46
1786455026 46
1786455031 46
1786455036 46
1786455041 46
1786455046 46
1786455051 51
1786455056 51
```
</details>

---

