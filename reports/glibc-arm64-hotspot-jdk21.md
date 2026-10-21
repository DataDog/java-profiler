---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 05:55:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 9 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 12 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792576328 43
1792576333 43
1792576338 43
1792576343 43
1792576348 43
1792576353 43
1792576358 43
1792576363 43
1792576368 43
1792576373 43
1792576378 43
1792576383 43
1792576388 43
1792576393 43
1792576398 43
1792576403 43
1792576408 43
1792576413 43
1792576418 43
1792576423 48
```
</details>

---

