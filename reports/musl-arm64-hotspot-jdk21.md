---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:15:30 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 10 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794582670 41
1794582675 41
1794582680 41
1794582685 46
1794582690 46
1794582695 46
1794582700 46
1794582705 46
1794582710 46
1794582715 46
1794582720 46
1794582725 46
1794582730 46
1794582735 46
1794582740 46
1794582745 46
1794582750 46
1794582755 46
1794582760 46
1794582765 46
```
</details>

---

