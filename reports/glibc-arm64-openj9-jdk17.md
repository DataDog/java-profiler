---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:25:37 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1789737654 43
1789737659 43
1789737664 43
1789737669 43
1789737674 43
1789737679 43
1789737684 43
1789737689 43
1789737694 43
1789737699 43
1789737704 43
1789737709 43
1789737714 43
1789737719 43
1789737724 43
1789737729 43
1789737734 42
1789737739 42
1789737744 42
1789737749 42
```
</details>

---

