---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 10:37:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 10-14 cores)</summary>

```
1786977219 10
1786977224 10
1786977229 10
1786977234 10
1786977239 10
1786977244 10
1786977249 10
1786977254 10
1786977259 10
1786977264 10
1786977269 10
1786977274 10
1786977279 10
1786977284 14
1786977289 14
1786977294 14
1786977299 14
1786977304 14
1786977309 14
1786977314 14
```
</details>

---

