---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 65-70 cores)</summary>

```
1773250196 67
1773250201 67
1773250206 67
1773250211 67
1773250216 67
1773250221 67
1773250226 67
1773250231 67
1773250236 67
1773250241 67
1773250246 67
1773250251 67
1773250256 67
1773250261 67
1773250266 67
1773250271 67
1773250276 67
1773250281 67
1773250286 70
1773250291 70
```
</details>

---

