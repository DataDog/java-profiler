---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 9-18 cores)</summary>

```
1789992184 9
1789992189 9
1789992194 9
1789992199 9
1789992204 9
1789992209 9
1789992214 9
1789992219 9
1789992224 9
1789992229 9
1789992234 9
1789992239 16
1789992244 16
1789992249 16
1789992254 16
1789992260 16
1789992265 16
1789992270 16
1789992275 16
1789992280 16
```
</details>

---

