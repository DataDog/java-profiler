---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 09:56:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 22-24 cores)</summary>

```
1795618286 24
1795618291 24
1795618296 24
1795618301 22
1795618306 22
1795618311 22
1795618316 22
1795618321 22
1795618326 22
1795618331 22
1795618336 22
1795618341 22
1795618346 22
1795618351 22
1795618356 23
1795618361 23
1795618366 23
1795618371 23
1795618376 23
1795618381 23
```
</details>

---

