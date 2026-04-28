---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 09:57:16 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 58-62 cores)</summary>

```
1777384224 58
1777384229 58
1777384234 58
1777384239 58
1777384244 62
1777384249 62
1777384254 62
1777384259 62
1777384264 62
1777384269 62
1777384274 62
1777384279 62
1777384284 62
1777384289 62
1777384294 62
1777384299 62
1777384304 62
1777384309 62
1777384314 62
1777384319 62
```
</details>

---

