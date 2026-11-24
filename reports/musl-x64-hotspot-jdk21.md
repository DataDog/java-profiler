---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 17:14:30 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (7 unique values: 44-67 cores)</summary>

```
1795558229 61
1795558234 67
1795558239 67
1795558244 65
1795558249 65
1795558254 65
1795558259 48
1795558264 48
1795558269 48
1795558274 48
1795558279 48
1795558284 48
1795558289 48
1795558294 48
1795558299 48
1795558304 48
1795558309 48
1795558314 48
1795558319 48
1795558324 48
```
</details>

---

