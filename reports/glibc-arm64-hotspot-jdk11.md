---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:01:13 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 965 |
| Sample Rate | 16.08/sec |
| Health Score | 1005% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1794326261 56
1794326266 56
1794326271 56
1794326276 56
1794326281 64
1794326286 64
1794326291 64
1794326296 64
1794326301 64
1794326306 64
1794326311 64
1794326316 64
1794326321 64
1794326326 64
1794326331 64
1794326336 64
1794326341 64
1794326346 64
1794326351 64
1794326356 64
```
</details>

---

