---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:27 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1786376471 67
1786376476 67
1786376481 67
1786376487 67
1786376492 67
1786376497 67
1786376502 67
1786376507 67
1786376512 65
1786376517 65
1786376522 65
1786376527 65
1786376532 65
1786376537 65
1786376542 65
1786376547 65
1786376552 65
1786376557 65
1786376562 65
1786376567 65
```
</details>

---

