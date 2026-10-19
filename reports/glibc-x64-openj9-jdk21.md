---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 16:23:29 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1792441165 92
1792441170 92
1792441175 92
1792441180 92
1792441185 92
1792441190 92
1792441195 92
1792441200 94
1792441205 94
1792441210 94
1792441215 94
1792441220 94
1792441225 94
1792441230 96
1792441235 96
1792441240 96
1792441245 96
1792441251 96
1792441256 96
1792441261 96
```
</details>

---

