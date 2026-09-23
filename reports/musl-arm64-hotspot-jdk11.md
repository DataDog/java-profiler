---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 11:28:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 18-36 cores)</summary>

```
1790177027 18
1790177032 18
1790177037 32
1790177042 32
1790177047 32
1790177052 32
1790177057 32
1790177062 32
1790177067 32
1790177072 32
1790177078 36
1790177083 36
1790177088 36
1790177093 36
1790177098 36
1790177103 36
1790177108 36
1790177113 36
1790177118 36
1790177123 36
```
</details>

---

