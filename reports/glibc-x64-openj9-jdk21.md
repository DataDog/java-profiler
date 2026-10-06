---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 09:30:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1791293047 16
1791293052 16
1791293057 16
1791293062 16
1791293067 16
1791293072 16
1791293077 16
1791293082 14
1791293087 14
1791293092 14
1791293097 14
1791293102 14
1791293107 14
1791293112 14
1791293117 14
1791293122 14
1791293127 14
1791293132 14
1791293137 14
1791293142 14
```
</details>

---

