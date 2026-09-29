---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 12:33:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 45-56 cores)</summary>

```
1790699276 49
1790699281 47
1790699286 47
1790699291 47
1790699296 47
1790699301 47
1790699306 47
1790699311 47
1790699316 47
1790699321 45
1790699326 45
1790699331 45
1790699336 45
1790699341 56
1790699346 56
1790699351 56
1790699356 56
1790699361 54
1790699366 54
1790699371 54
```
</details>

---

