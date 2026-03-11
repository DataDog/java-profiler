---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-11 13:39:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1773250186 32
1773250191 32
1773250196 32
1773250201 32
1773250206 32
1773250211 32
1773250216 32
1773250221 32
1773250226 32
1773250231 32
1773250236 32
1773250241 32
1773250246 32
1773250251 32
1773250256 32
1773250261 30
1773250266 30
1773250271 30
1773250276 30
1773250281 30
```
</details>

---

