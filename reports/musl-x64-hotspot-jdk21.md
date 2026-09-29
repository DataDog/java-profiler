---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 90-96 cores)</summary>

```
1790699301 90
1790699306 90
1790699311 90
1790699316 90
1790699321 90
1790699326 90
1790699331 90
1790699336 96
1790699341 96
1790699346 96
1790699351 96
1790699356 96
1790699361 96
1790699366 96
1790699371 96
1790699376 96
1790699381 96
1790699386 96
1790699391 96
1790699396 96
```
</details>

---

