---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:40:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1794504882 87
1794504887 87
1794504892 87
1794504897 85
1794504902 85
1794504907 85
1794504912 85
1794504917 85
1794504922 85
1794504927 85
1794504932 85
1794504937 85
1794504942 85
1794504947 85
1794504952 85
1794504957 87
1794504962 87
1794504967 87
1794504973 87
1794504978 87
```
</details>

---

