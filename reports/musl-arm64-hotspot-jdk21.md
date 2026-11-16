---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:44:16 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 12 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794843613 46
1794843618 46
1794843623 46
1794843628 46
1794843633 46
1794843638 46
1794843643 46
1794843648 48
1794843653 48
1794843658 48
1794843663 48
1794843668 48
1794843673 48
1794843678 48
1794843683 48
1794843688 48
1794843693 48
1794843698 48
1794843703 48
1794843708 48
```
</details>

---

