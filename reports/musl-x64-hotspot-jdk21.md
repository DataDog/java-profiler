---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-20 01:00:37 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1789880145 79
1789880150 79
1789880155 79
1789880160 79
1789880165 79
1789880170 79
1789880175 79
1789880180 81
1789880185 81
1789880190 79
1789880195 79
1789880200 79
1789880205 79
1789880210 79
1789880215 79
1789880220 79
1789880225 79
1789880230 79
1789880235 79
1789880240 81
```
</details>

---

