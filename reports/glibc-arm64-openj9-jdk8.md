---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-01 09:06:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 32-48 cores)</summary>

```
1790859712 37
1790859717 37
1790859722 37
1790859727 37
1790859732 37
1790859737 37
1790859742 37
1790859747 37
1790859752 37
1790859757 37
1790859762 37
1790859767 32
1790859772 32
1790859777 32
1790859782 32
1790859787 41
1790859792 41
1790859797 41
1790859802 41
1790859807 46
```
</details>

---

