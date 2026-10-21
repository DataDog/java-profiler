---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 16:58:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1792615971 91
1792615976 91
1792615981 91
1792615986 91
1792615991 91
1792615996 91
1792616001 91
1792616006 91
1792616011 91
1792616016 91
1792616021 91
1792616026 91
1792616031 91
1792616036 93
1792616041 93
1792616046 93
1792616051 93
1792616056 93
1792616061 93
1792616066 93
```
</details>

---

