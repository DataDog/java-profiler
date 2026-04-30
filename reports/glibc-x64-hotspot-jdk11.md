---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 86-93 cores)</summary>

```
1777557415 86
1777557420 86
1777557425 86
1777557430 88
1777557435 88
1777557440 88
1777557445 88
1777557450 88
1777557455 88
1777557460 88
1777557465 93
1777557470 93
1777557475 93
1777557480 93
1777557485 93
1777557490 93
1777557495 93
1777557500 93
1777557505 93
1777557510 93
```
</details>

---

