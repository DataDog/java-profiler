---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 17:52:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 13-18 cores)</summary>

```
1792532782 15
1792532787 15
1792532792 13
1792532797 13
1792532802 13
1792532807 13
1792532812 13
1792532817 13
1792532822 13
1792532827 13
1792532832 13
1792532837 13
1792532842 13
1792532847 13
1792532852 13
1792532857 13
1792532862 13
1792532867 13
1792532872 13
1792532877 13
```
</details>

---

