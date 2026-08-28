---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-28 14:02:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787939892 64
1787939897 64
1787939902 64
1787939907 64
1787939912 64
1787939917 64
1787939922 64
1787939927 64
1787939932 64
1787939937 64
1787939942 64
1787939947 64
1787939952 64
1787939957 64
1787939962 64
1787939967 64
1787939972 64
1787939977 64
1787939982 64
1787939987 64
```
</details>

---

