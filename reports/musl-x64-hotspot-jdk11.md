---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:58:20 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 37-46 cores)</summary>

```
1790571187 37
1790571192 37
1790571197 37
1790571202 37
1790571207 37
1790571212 37
1790571217 37
1790571222 37
1790571227 37
1790571232 46
1790571237 46
1790571242 46
1790571247 46
1790571252 46
1790571257 46
1790571262 46
1790571267 46
1790571272 46
1790571277 46
1790571282 46
```
</details>

---

