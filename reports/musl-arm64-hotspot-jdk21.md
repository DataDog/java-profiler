---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:39:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1791531231 24
1791531236 24
1791531241 24
1791531246 24
1791531251 24
1791531256 24
1791531261 24
1791531266 24
1791531271 24
1791531276 29
1791531281 29
1791531286 29
1791531291 29
1791531296 29
1791531301 29
1791531306 29
1791531311 29
1791531316 29
1791531321 29
1791531326 29
```
</details>

---

