---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 08:24:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 14 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787055674 32
1787055679 32
1787055684 32
1787055689 32
1787055694 32
1787055699 32
1787055704 32
1787055709 32
1787055714 32
1787055719 32
1787055724 32
1787055729 32
1787055734 32
1787055739 32
1787055744 32
1787055749 32
1787055754 32
1787055759 32
1787055764 32
1787055769 32
```
</details>

---

