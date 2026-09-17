---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:53:19 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 35-91 cores)</summary>

```
1789667192 35
1789667197 35
1789667202 35
1789667207 35
1789667212 35
1789667217 71
1789667222 71
1789667227 71
1789667232 71
1789667237 71
1789667242 71
1789667247 71
1789667252 71
1789667257 71
1789667262 71
1789667267 71
1789667272 71
1789667277 71
1789667282 71
1789667287 91
```
</details>

---

