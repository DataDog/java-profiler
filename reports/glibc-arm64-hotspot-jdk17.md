---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:03:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793620775 48
1793620780 48
1793620785 48
1793620790 48
1793620795 48
1793620800 48
1793620805 48
1793620810 48
1793620815 48
1793620820 48
1793620825 48
1793620830 48
1793620835 48
1793620841 43
1793620846 43
1793620851 43
1793620856 43
1793620861 43
1793620866 43
1793620871 43
```
</details>

---

