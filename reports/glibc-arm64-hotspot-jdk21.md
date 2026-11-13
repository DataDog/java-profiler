---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:25:06 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 20-21 cores)</summary>

```
1794572441 20
1794572446 20
1794572451 20
1794572456 20
1794572461 20
1794572466 20
1794572471 20
1794572476 20
1794572481 20
1794572486 20
1794572491 20
1794572496 20
1794572501 20
1794572506 21
1794572511 21
1794572516 21
1794572521 21
1794572526 21
1794572531 21
1794572536 21
```
</details>

---

