---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 21:17:46 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793409206 40
1793409211 40
1793409216 40
1793409221 40
1793409226 40
1793409231 40
1793409236 40
1793409241 40
1793409246 40
1793409251 40
1793409256 40
1793409261 40
1793409266 40
1793409271 40
1793409276 40
1793409281 40
1793409286 40
1793409291 40
1793409296 40
1793409301 40
```
</details>

---

