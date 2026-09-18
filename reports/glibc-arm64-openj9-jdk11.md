---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:27:48 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1789737696 44
1789737701 44
1789737706 44
1789737711 44
1789737716 44
1789737721 44
1789737726 44
1789737731 44
1789737736 44
1789737741 44
1789737746 44
1789737751 44
1789737756 44
1789737761 44
1789737766 44
1789737771 44
1789737776 48
1789737781 48
1789737786 48
1789737791 48
```
</details>

---

