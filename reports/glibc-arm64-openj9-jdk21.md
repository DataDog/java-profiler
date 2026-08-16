---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-16 11:16:13 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786893091 43
1786893096 43
1786893101 43
1786893106 43
1786893111 43
1786893116 43
1786893121 43
1786893126 43
1786893132 43
1786893137 43
1786893142 43
1786893147 43
1786893152 43
1786893157 43
1786893162 43
1786893167 43
1786893172 43
1786893177 43
1786893182 43
1786893187 48
```
</details>

---

