---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 79-90 cores)</summary>

```
1793812780 79
1793812785 79
1793812790 79
1793812795 79
1793812800 79
1793812805 81
1793812810 81
1793812815 81
1793812820 81
1793812825 81
1793812830 81
1793812835 81
1793812840 81
1793812845 81
1793812850 81
1793812855 81
1793812860 90
1793812865 90
1793812870 90
1793812875 90
```
</details>

---

