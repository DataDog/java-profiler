---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 05:55:44 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 15 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (4 unique values: 36-42 cores)</summary>

```
1791280169 37
1791280174 37
1791280179 42
1791280184 42
1791280189 41
1791280194 41
1791280199 41
1791280204 41
1791280209 41
1791280214 41
1791280219 41
1791280224 41
1791280229 36
1791280234 36
1791280239 36
1791280244 36
1791280249 36
1791280254 37
1791280259 37
1791280264 37
```
</details>

---

