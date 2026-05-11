---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:12 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 12 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1778512732 57
1778512737 57
1778512742 57
1778512747 57
1778512752 57
1778512757 57
1778512762 57
1778512767 57
1778512772 57
1778512777 57
1778512782 57
1778512787 57
1778512792 57
1778512797 64
1778512802 64
1778512807 64
1778512812 64
1778512817 53
1778512822 53
1778512827 53
```
</details>

---

