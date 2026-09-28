---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 00:58:20 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 31-66 cores)</summary>

```
1790571197 31
1790571202 31
1790571207 31
1790571212 31
1790571217 31
1790571222 31
1790571227 31
1790571232 31
1790571237 31
1790571242 33
1790571247 33
1790571252 33
1790571257 33
1790571262 33
1790571267 33
1790571272 33
1790571277 33
1790571283 33
1790571288 33
1790571293 33
```
</details>

---

