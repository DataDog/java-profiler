---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:31:20 EDT

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
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (5 unique values: 27-44 cores)</summary>

```
1789737702 44
1789737707 32
1789737712 32
1789737717 32
1789737722 32
1789737727 32
1789737732 32
1789737737 32
1789737742 32
1789737747 27
1789737752 27
1789737757 27
1789737762 27
1789737767 27
1789737772 27
1789737777 31
1789737782 31
1789737787 31
1789737792 31
1789737797 36
```
</details>

---

