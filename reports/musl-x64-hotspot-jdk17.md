---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 05:48:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 37-81 cores)</summary>

```
1786354966 37
1786354971 37
1786354976 78
1786354981 78
1786354986 81
1786354991 81
1786354996 81
1786355001 81
1786355006 81
1786355011 81
1786355016 81
1786355021 81
1786355026 81
1786355031 81
1786355036 81
1786355041 81
1786355046 81
1786355051 81
1786355056 81
1786355061 81
```
</details>

---

