---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 74-82 cores)</summary>

```
1777325201 80
1777325206 80
1777325211 80
1777325216 80
1777325221 80
1777325226 80
1777325231 80
1777325236 77
1777325241 77
1777325246 77
1777325251 77
1777325256 77
1777325261 77
1777325266 82
1777325271 82
1777325276 82
1777325281 82
1777325286 82
1777325291 82
1777325296 82
```
</details>

---

