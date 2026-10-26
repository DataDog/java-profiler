---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:57:44 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 77-96 cores)</summary>

```
1793019113 77
1793019118 77
1793019123 77
1793019128 77
1793019133 77
1793019138 77
1793019143 77
1793019148 96
1793019153 96
1793019158 96
1793019163 96
1793019168 96
1793019173 96
1793019178 96
1793019183 96
1793019188 96
1793019193 96
1793019198 96
1793019203 96
1793019208 96
```
</details>

---

