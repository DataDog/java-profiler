---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:14:25 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 16-33 cores)</summary>

```
1793880552 16
1793880557 16
1793880562 18
1793880567 18
1793880572 20
1793880577 20
1793880582 20
1793880587 20
1793880592 20
1793880597 20
1793880602 20
1793880607 20
1793880612 20
1793880617 20
1793880622 20
1793880628 20
1793880633 20
1793880638 20
1793880643 20
1793880648 20
```
</details>

---

