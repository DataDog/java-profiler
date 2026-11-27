---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:24:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 64-85 cores)</summary>

```
1795785586 64
1795785591 64
1795785596 64
1795785601 64
1795785606 64
1795785611 85
1795785616 85
1795785621 85
1795785626 85
1795785631 85
1795785636 85
1795785641 85
1795785646 85
1795785651 85
1795785656 85
1795785661 85
1795785666 85
1795785671 85
1795785676 85
1795785681 85
```
</details>

---

