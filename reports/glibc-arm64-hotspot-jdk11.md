---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 11:55:08 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1786636256 48
1786636261 48
1786636266 48
1786636271 48
1786636276 48
1786636281 43
1786636286 43
1786636291 43
1786636296 43
1786636301 43
1786636306 43
1786636311 43
1786636316 43
1786636321 43
1786636326 43
1786636331 43
1786636336 43
1786636341 48
1786636346 48
1786636351 48
```
</details>

---

