---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 52-56 cores)</summary>

```
1777325196 56
1777325201 56
1777325206 52
1777325211 52
1777325216 52
1777325221 52
1777325226 52
1777325231 52
1777325236 52
1777325241 52
1777325246 52
1777325251 52
1777325256 52
1777325261 52
1777325266 52
1777325271 52
1777325276 52
1777325282 52
1777325287 52
1777325292 52
```
</details>

---

