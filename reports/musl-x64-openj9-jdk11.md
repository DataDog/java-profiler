---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:15:34 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 15-60 cores)</summary>

```
1777324037 18
1777324042 18
1777324047 20
1777324052 20
1777324057 20
1777324062 20
1777324067 20
1777324072 20
1777324077 15
1777324082 15
1777324087 15
1777324092 15
1777324097 15
1777324102 15
1777324107 15
1777324112 15
1777324117 15
1777324122 15
1777324127 15
1777324132 35
```
</details>

---

