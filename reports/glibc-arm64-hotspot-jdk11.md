---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:39:35 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 26-35 cores)</summary>

```
1791531251 35
1791531256 35
1791531261 35
1791531266 35
1791531271 35
1791531276 35
1791531281 35
1791531286 35
1791531291 35
1791531296 35
1791531301 35
1791531306 35
1791531311 35
1791531316 31
1791531321 31
1791531326 29
1791531331 29
1791531336 29
1791531341 29
1791531346 29
```
</details>

---

