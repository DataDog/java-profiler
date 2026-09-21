---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:41:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1789979852 37
1789979857 37
1789979862 37
1789979867 40
1789979872 40
1789979877 40
1789979882 40
1789979887 40
1789979892 40
1789979897 40
1789979902 40
1789979907 40
1789979912 40
1789979917 40
1789979922 40
1789979927 40
1789979932 40
1789979937 40
1789979942 40
1789979947 40
```
</details>

---

