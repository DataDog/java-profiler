---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 51-57 cores)</summary>

```
1789992212 51
1789992217 51
1789992222 51
1789992227 53
1789992232 53
1789992237 55
1789992242 55
1789992247 55
1789992252 55
1789992257 55
1789992262 55
1789992267 55
1789992272 55
1789992277 55
1789992282 57
1789992288 57
1789992293 57
1789992298 57
1789992303 57
1789992308 57
```
</details>

---

