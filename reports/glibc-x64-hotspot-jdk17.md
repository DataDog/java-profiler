---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 07:48:12 EST

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
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 80-85 cores)</summary>

```
1795783424 82
1795783429 82
1795783434 82
1795783439 82
1795783444 82
1795783449 82
1795783454 82
1795783459 82
1795783464 82
1795783469 82
1795783474 82
1795783479 82
1795783484 82
1795783489 82
1795783494 82
1795783499 80
1795783504 80
1795783509 80
1795783514 80
1795783519 80
```
</details>

---

