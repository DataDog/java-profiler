---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 02:24:36 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 19-31 cores)</summary>

```
1786429196 21
1786429201 21
1786429206 21
1786429211 21
1786429216 19
1786429222 19
1786429227 19
1786429232 19
1786429237 19
1786429242 19
1786429247 19
1786429252 19
1786429257 19
1786429262 27
1786429267 27
1786429272 29
1786429277 29
1786429282 31
1786429287 31
1786429292 31
```
</details>

---

