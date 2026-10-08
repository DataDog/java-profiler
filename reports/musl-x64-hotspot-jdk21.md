---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:10:23 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 42-51 cores)</summary>

```
1791468212 44
1791468217 44
1791468222 42
1791468227 42
1791468232 42
1791468237 42
1791468242 44
1791468247 44
1791468252 44
1791468257 44
1791468262 46
1791468267 46
1791468272 51
1791468277 51
1791468282 51
1791468287 51
1791468292 51
1791468297 51
1791468302 51
1791468307 51
```
</details>

---

