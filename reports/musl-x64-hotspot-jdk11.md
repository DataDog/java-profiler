---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 08:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (4 unique values: 26-75 cores)</summary>

```
1795181247 26
1795181252 26
1795181257 48
1795181262 48
1795181267 48
1795181272 55
1795181277 55
1795181282 75
1795181287 75
1795181292 75
1795181297 75
1795181302 75
1795181307 75
1795181312 75
1795181317 75
1795181322 75
1795181327 75
1795181332 75
1795181337 75
1795181342 75
```
</details>

---

