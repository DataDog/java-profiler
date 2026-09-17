---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:33:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 66-75 cores)</summary>

```
1789680182 66
1789680187 66
1789680192 66
1789680197 66
1789680202 66
1789680207 66
1789680212 75
1789680217 75
1789680222 73
1789680227 73
1789680232 73
1789680237 73
1789680242 73
1789680247 73
1789680252 73
1789680257 73
1789680262 73
1789680267 73
1789680272 75
1789680277 75
```
</details>

---

