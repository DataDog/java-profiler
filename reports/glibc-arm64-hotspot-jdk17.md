---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:55:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1794394270 45
1794394275 45
1794394280 45
1794394285 45
1794394290 45
1794394295 45
1794394300 40
1794394305 40
1794394310 42
1794394315 42
1794394320 43
1794394325 43
1794394330 43
1794394335 43
1794394340 43
1794394345 43
1794394350 43
1794394355 43
1794394360 48
1794394365 48
```
</details>

---

