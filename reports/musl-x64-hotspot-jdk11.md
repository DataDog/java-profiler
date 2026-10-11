---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 15:21:54 EDT

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
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1791746250 32
1791746255 32
1791746260 32
1791746265 32
1791746270 32
1791746275 19
1791746280 19
1791746285 19
1791746290 19
1791746295 19
1791746300 19
1791746305 19
1791746310 19
1791746315 19
1791746320 19
1791746325 19
1791746330 19
1791746335 19
1791746340 19
1791746345 19
```
</details>

---

