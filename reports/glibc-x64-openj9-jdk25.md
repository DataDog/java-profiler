---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:25:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 12 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1794583278 82
1794583283 82
1794583288 82
1794583293 82
1794583298 82
1794583303 82
1794583308 82
1794583313 82
1794583318 82
1794583323 82
1794583328 82
1794583333 82
1794583338 82
1794583343 84
1794583348 84
1794583353 84
1794583358 84
1794583363 84
1794583368 84
1794583373 84
```
</details>

---

