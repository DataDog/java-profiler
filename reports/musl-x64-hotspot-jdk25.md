---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:10:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1791468192 75
1791468197 75
1791468202 75
1791468207 75
1791468212 75
1791468217 73
1791468222 73
1791468227 73
1791468232 73
1791468237 73
1791468242 73
1791468247 73
1791468252 73
1791468257 69
1791468262 69
1791468267 69
1791468272 69
1791468277 71
1791468282 71
1791468287 71
```
</details>

---

