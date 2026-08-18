---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 21:38:41 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 11 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787016843 48
1787016848 48
1787016853 43
1787016858 43
1787016863 43
1787016868 43
1787016873 43
1787016878 43
1787016883 43
1787016888 43
1787016893 43
1787016898 43
1787016903 48
1787016908 48
1787016913 48
1787016918 48
1787016923 48
1787016928 48
1787016933 48
1787016938 48
```
</details>

---

