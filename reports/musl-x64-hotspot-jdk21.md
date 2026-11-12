---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:52:04 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (6 unique values: 77-94 cores)</summary>

```
1794498184 77
1794498189 77
1794498194 77
1794498199 77
1794498204 79
1794498209 79
1794498214 79
1794498219 79
1794498224 79
1794498229 83
1794498234 83
1794498239 87
1794498244 87
1794498249 87
1794498254 87
1794498259 87
1794498264 87
1794498269 87
1794498274 89
1794498279 89
```
</details>

---

