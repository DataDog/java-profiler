---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 18:25:48 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 15 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1792707757 44
1792707762 44
1792707767 44
1792707772 44
1792707777 44
1792707782 44
1792707787 44
1792707792 44
1792707797 44
1792707802 44
1792707807 44
1792707812 24
1792707817 24
1792707822 24
1792707827 24
1792707832 24
1792707837 24
1792707842 24
1792707847 24
1792707852 24
```
</details>

---

