---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 13:09:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 11 |
| Allocations | 208 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791306214 43
1791306219 48
1791306224 48
1791306229 48
1791306234 48
1791306239 48
1791306244 48
1791306249 48
1791306254 48
1791306259 48
1791306264 48
1791306269 48
1791306274 48
1791306279 48
1791306284 48
1791306289 43
1791306294 43
1791306299 43
1791306304 43
1791306309 43
```
</details>

---

