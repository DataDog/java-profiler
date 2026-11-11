---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:16:30 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (5 unique values: 31-48 cores)</summary>

```
1794435097 48
1794435102 48
1794435107 48
1794435112 48
1794435117 48
1794435122 48
1794435127 43
1794435132 43
1794435137 43
1794435142 43
1794435147 43
1794435152 43
1794435157 43
1794435162 43
1794435167 38
1794435172 38
1794435177 38
1794435182 38
1794435187 38
1794435192 38
```
</details>

---

