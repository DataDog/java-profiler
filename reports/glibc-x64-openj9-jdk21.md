---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (7 unique values: 70-86 cores)</summary>

```
1777321212 70
1777321217 70
1777321222 70
1777321227 70
1777321232 74
1777321237 74
1777321242 79
1777321247 79
1777321252 79
1777321257 79
1777321262 79
1777321267 79
1777321272 79
1777321277 79
1777321282 79
1777321287 77
1777321292 77
1777321297 77
1777321302 77
1777321307 81
```
</details>

---

