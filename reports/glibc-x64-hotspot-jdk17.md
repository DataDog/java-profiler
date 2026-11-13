---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:25:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 10 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1794572421 82
1794572426 82
1794572431 82
1794572436 82
1794572441 82
1794572446 82
1794572451 82
1794572456 82
1794572461 82
1794572466 82
1794572471 84
1794572476 84
1794572481 84
1794572486 84
1794572491 84
1794572496 84
1794572501 84
1794572506 84
1794572511 84
1794572516 84
```
</details>

---

