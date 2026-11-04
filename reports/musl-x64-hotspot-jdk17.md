---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 37-57 cores)</summary>

```
1793829484 37
1793829489 37
1793829494 37
1793829499 37
1793829504 37
1793829509 37
1793829514 37
1793829519 37
1793829524 37
1793829529 37
1793829534 37
1793829539 37
1793829544 57
1793829549 57
1793829554 57
1793829559 57
1793829564 57
1793829569 57
1793829574 57
1793829579 57
```
</details>

---

