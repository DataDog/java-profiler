---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 05:39:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770114882 32
1770114887 32
1770114892 32
1770114897 32
1770114902 32
1770114907 32
1770114912 32
1770114917 32
1770114922 32
1770114927 32
1770114932 32
1770114937 32
1770114942 32
1770114947 32
1770114952 31
1770114957 31
1770114962 32
1770114967 32
1770114972 32
1770114977 32
```
</details>

---

