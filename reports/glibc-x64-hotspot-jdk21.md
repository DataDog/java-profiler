---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 11:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 11 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 41-59 cores)</summary>

```
1795796656 41
1795796661 41
1795796666 41
1795796671 41
1795796676 41
1795796681 41
1795796686 41
1795796691 41
1795796696 41
1795796701 57
1795796706 57
1795796711 57
1795796716 57
1795796721 57
1795796726 57
1795796731 57
1795796736 57
1795796741 57
1795796746 57
1795796751 57
```
</details>

---

