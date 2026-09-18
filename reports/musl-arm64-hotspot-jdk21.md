---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 05:50:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1789724617 48
1789724622 48
1789724627 48
1789724632 48
1789724637 48
1789724642 48
1789724647 48
1789724652 48
1789724657 48
1789724662 48
1789724667 48
1789724672 44
1789724677 44
1789724682 44
1789724687 44
1789724692 44
1789724697 44
1789724702 44
1789724707 44
1789724712 44
```
</details>

---

