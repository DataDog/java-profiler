---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:47:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 40-61 cores)</summary>

```
1793644961 42
1793644966 42
1793644971 42
1793644976 42
1793644981 42
1793644986 42
1793644991 42
1793644996 42
1793645001 42
1793645006 42
1793645011 42
1793645016 42
1793645021 42
1793645026 42
1793645031 42
1793645036 42
1793645041 40
1793645046 40
1793645051 40
1793645056 40
```
</details>

---

