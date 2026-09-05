---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 22:42:04 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1788575857 14
1788575862 14
1788575867 14
1788575872 14
1788575877 34
1788575882 34
1788575887 34
1788575892 34
1788575897 34
1788575902 34
1788575907 34
1788575912 34
1788575917 34
1788575922 34
1788575927 34
1788575932 34
1788575937 34
1788575942 34
1788575947 34
1788575952 34
```
</details>

---

