---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:30:03 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1794245017 28
1794245022 28
1794245027 28
1794245032 28
1794245037 30
1794245042 30
1794245047 30
1794245052 30
1794245057 30
1794245062 30
1794245067 30
1794245072 30
1794245077 30
1794245082 30
1794245087 30
1794245092 30
1794245097 30
1794245103 30
1794245108 30
1794245113 30
```
</details>

---

