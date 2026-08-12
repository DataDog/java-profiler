---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-12 05:20:33 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-71 cores)</summary>

```
1786526151 50
1786526156 50
1786526161 50
1786526166 50
1786526171 50
1786526176 71
1786526181 71
1786526186 71
1786526191 71
1786526196 71
1786526201 71
1786526206 71
1786526211 71
1786526216 71
1786526221 71
1786526226 71
1786526231 71
1786526236 71
1786526241 71
1786526246 71
```
</details>

---

