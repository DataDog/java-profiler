---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:48:35 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 57-81 cores)</summary>

```
1795113776 57
1795113781 57
1795113786 57
1795113791 57
1795113796 57
1795113801 57
1795113806 57
1795113811 57
1795113816 57
1795113821 57
1795113826 79
1795113831 79
1795113836 79
1795113841 79
1795113846 79
1795113851 79
1795113856 79
1795113861 79
1795113866 79
1795113871 81
```
</details>

---

