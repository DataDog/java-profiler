---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:38:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (3 unique values: 17-27 cores)</summary>

```
1770125644 22
1770125649 22
1770125654 22
1770125659 22
1770125664 22
1770125669 17
1770125674 17
1770125679 27
1770125684 27
1770125689 27
1770125694 27
1770125699 27
1770125704 27
1770125709 27
1770125714 27
1770125719 27
1770125724 27
1770125729 27
1770125734 27
1770125739 27
```
</details>

---

