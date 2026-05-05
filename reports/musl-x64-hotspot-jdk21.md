---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 955 |
| Sample Rate | 15.92/sec |
| Health Score | 995% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 47-57 cores)</summary>

```
1777983463 57
1777983468 57
1777983473 57
1777983478 57
1777983483 57
1777983488 52
1777983493 52
1777983498 52
1777983503 52
1777983508 52
1777983513 52
1777983518 52
1777983523 52
1777983528 47
1777983533 47
1777983538 47
1777983543 47
1777983548 47
1777983553 47
1777983558 47
```
</details>

---

