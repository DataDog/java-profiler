---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793620780 32
1793620785 32
1793620790 32
1793620795 32
1793620801 32
1793620806 32
1793620811 32
1793620816 32
1793620821 32
1793620826 32
1793620831 32
1793620836 32
1793620841 32
1793620846 32
1793620851 32
1793620856 32
1793620861 32
1793620866 32
1793620871 32
1793620876 32
```
</details>

---

