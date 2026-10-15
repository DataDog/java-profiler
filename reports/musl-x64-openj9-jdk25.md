---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 05:55:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1792057857 84
1792057862 84
1792057867 84
1792057872 80
1792057877 80
1792057882 80
1792057887 82
1792057892 82
1792057897 82
1792057902 84
1792057907 84
1792057912 84
1792057917 84
1792057922 84
1792057927 84
1792057932 82
1792057937 82
1792057942 82
1792057947 82
1792057952 82
```
</details>

---

