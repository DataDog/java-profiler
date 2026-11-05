---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 05:59:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 10 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1793876056 51
1793876061 51
1793876066 51
1793876071 51
1793876076 51
1793876082 51
1793876087 51
1793876092 51
1793876097 47
1793876102 47
1793876107 47
1793876112 47
1793876117 47
1793876122 47
1793876127 47
1793876132 47
1793876137 47
1793876142 47
1793876147 47
1793876152 47
```
</details>

---

