---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:44 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 72-79 cores)</summary>

```
1793995706 72
1793995711 72
1793995716 72
1793995721 72
1793995726 75
1793995731 75
1793995736 73
1793995741 73
1793995746 73
1793995751 73
1793995756 73
1793995761 73
1793995766 73
1793995771 73
1793995776 73
1793995781 73
1793995786 73
1793995791 73
1793995796 73
1793995801 79
```
</details>

---

