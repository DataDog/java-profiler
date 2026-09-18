---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:25:37 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 9 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1789737724 44
1789737729 44
1789737734 44
1789737739 44
1789737744 44
1789737749 44
1789737754 44
1789737759 44
1789737764 44
1789737769 44
1789737774 48
1789737779 48
1789737784 48
1789737789 48
1789737794 48
1789737799 48
1789737804 48
1789737809 48
1789737814 48
1789737819 48
```
</details>

---

