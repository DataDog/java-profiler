---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 48-58 cores)</summary>

```
1789995777 58
1789995782 58
1789995787 58
1789995792 58
1789995797 58
1789995802 58
1789995807 58
1789995812 58
1789995817 58
1789995822 58
1789995828 58
1789995833 58
1789995838 58
1789995843 58
1789995848 48
1789995853 48
1789995858 48
1789995863 48
1789995868 48
1789995873 48
```
</details>

---

