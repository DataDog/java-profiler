---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 01:06:17 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 11 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1792731624 40
1792731629 40
1792731634 40
1792731639 40
1792731644 40
1792731649 40
1792731654 40
1792731659 40
1792731664 40
1792731669 40
1792731674 40
1792731679 40
1792731684 40
1792731689 40
1792731694 40
1792731699 40
1792731704 40
1792731709 40
1792731714 35
1792731719 35
```
</details>

---

