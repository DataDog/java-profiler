---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:49:38 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 74-77 cores)</summary>

```
1793295791 77
1793295796 77
1793295801 77
1793295806 77
1793295811 77
1793295816 77
1793295821 77
1793295826 77
1793295831 77
1793295836 77
1793295841 77
1793295846 77
1793295851 76
1793295856 76
1793295861 76
1793295866 76
1793295871 76
1793295876 76
1793295881 76
1793295886 74
```
</details>

---

