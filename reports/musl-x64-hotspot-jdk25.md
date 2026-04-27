---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 28-43 cores)</summary>

```
1777325157 43
1777325162 43
1777325167 43
1777325172 43
1777325177 43
1777325182 43
1777325187 43
1777325192 43
1777325197 43
1777325202 43
1777325207 43
1777325212 43
1777325217 43
1777325222 43
1777325227 43
1777325232 43
1777325237 28
1777325242 28
1777325247 28
1777325252 28
```
</details>

---

