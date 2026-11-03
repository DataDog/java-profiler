---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 52-61 cores)</summary>

```
1793742191 59
1793742196 61
1793742201 61
1793742206 61
1793742211 61
1793742216 61
1793742221 61
1793742226 61
1793742231 61
1793742236 52
1793742241 52
1793742246 52
1793742251 52
1793742256 52
1793742261 52
1793742266 52
1793742271 52
1793742276 52
1793742281 52
1793742286 52
```
</details>

---

