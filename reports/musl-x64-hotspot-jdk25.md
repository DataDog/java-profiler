---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:07:40 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 11 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 13 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 41-44 cores)</summary>

```
1773252151 42
1773252156 42
1773252161 42
1773252166 42
1773252171 42
1773252176 42
1773252181 44
1773252186 44
1773252191 44
1773252196 44
1773252201 44
1773252206 44
1773252211 44
1773252216 44
1773252221 44
1773252226 44
1773252231 44
1773252236 44
1773252241 41
1773252246 41
```
</details>

---

