---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:30:46 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 47-59 cores)</summary>

```
1777559096 59
1777559101 59
1777559106 59
1777559111 59
1777559116 59
1777559121 59
1777559126 59
1777559131 59
1777559136 55
1777559141 55
1777559146 55
1777559151 55
1777559156 55
1777559161 55
1777559166 50
1777559171 50
1777559176 50
1777559181 50
1777559186 50
1777559191 50
```
</details>

---

