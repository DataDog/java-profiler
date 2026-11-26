---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 28-47 cores)</summary>

```
1795705999 28
1795706004 28
1795706009 28
1795706014 28
1795706019 28
1795706024 28
1795706029 28
1795706034 28
1795706039 28
1795706044 28
1795706049 47
1795706054 47
1795706059 47
1795706064 47
1795706069 47
1795706074 47
1795706079 47
1795706084 47
1795706089 47
1795706094 47
```
</details>

---

