---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 63-71 cores)</summary>

```
1793995706 71
1793995711 71
1793995716 71
1793995721 71
1793995726 71
1793995731 71
1793995736 66
1793995741 66
1793995746 63
1793995751 63
1793995756 63
1793995761 63
1793995766 63
1793995771 63
1793995776 63
1793995781 63
1793995786 63
1793995791 63
1793995796 63
1793995801 63
```
</details>

---

