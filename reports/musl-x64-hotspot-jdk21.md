---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:16:20 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (6 unique values: 46-71 cores)</summary>

```
1794823663 51
1794823668 51
1794823673 49
1794823678 49
1794823683 49
1794823688 49
1794823693 49
1794823698 49
1794823703 49
1794823708 49
1794823713 49
1794823718 46
1794823723 46
1794823728 46
1794823733 46
1794823738 67
1794823744 67
1794823749 67
1794823754 69
1794823759 69
```
</details>

---

