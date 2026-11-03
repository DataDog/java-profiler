---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:51:02 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 49-57 cores)</summary>

```
1793742191 49
1793742196 49
1793742201 49
1793742206 49
1793742211 49
1793742216 49
1793742221 49
1793742226 49
1793742231 49
1793742236 49
1793742241 49
1793742246 57
1793742251 57
1793742256 57
1793742261 57
1793742266 57
1793742271 57
1793742276 57
1793742281 57
1793742286 57
```
</details>

---

