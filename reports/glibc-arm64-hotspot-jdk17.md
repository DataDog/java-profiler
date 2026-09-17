---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:10:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1789686381 48
1789686386 48
1789686391 48
1789686396 48
1789686401 28
1789686406 28
1789686411 28
1789686416 28
1789686421 28
1789686426 28
1789686431 28
1789686436 28
1789686441 28
1789686446 28
1789686451 28
1789686456 28
1789686461 28
1789686466 28
1789686471 28
1789686476 28
```
</details>

---

