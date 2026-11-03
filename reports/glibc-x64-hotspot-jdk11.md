---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1793721412 82
1793721417 82
1793721422 82
1793721427 82
1793721432 82
1793721437 84
1793721442 84
1793721447 84
1793721452 84
1793721457 84
1793721462 84
1793721467 84
1793721472 84
1793721477 84
1793721482 86
1793721487 86
1793721492 86
1793721497 86
1793721502 86
1793721507 86
```
</details>

---

