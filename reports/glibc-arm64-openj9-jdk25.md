---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 06:11:53 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 13 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789639678 43
1789639683 43
1789639688 43
1789639693 43
1789639698 43
1789639703 43
1789639708 43
1789639713 48
1789639718 48
1789639723 48
1789639728 48
1789639733 48
1789639738 48
1789639743 48
1789639748 48
1789639753 48
1789639758 48
1789639763 48
1789639768 48
1789639773 48
```
</details>

---

