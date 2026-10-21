---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 16:58:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 57-92 cores)</summary>

```
1792615967 92
1792615972 92
1792615977 92
1792615982 92
1792615987 57
1792615992 57
1792615997 59
1792616002 59
1792616007 59
1792616012 59
1792616017 59
1792616022 59
1792616027 59
1792616032 59
1792616037 59
1792616042 59
1792616047 59
1792616052 59
1792616057 59
1792616062 59
```
</details>

---

