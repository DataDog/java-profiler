---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 05:36:50 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 9 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795602652 32
1795602657 32
1795602662 32
1795602667 32
1795602672 32
1795602677 32
1795602682 32
1795602687 32
1795602692 32
1795602697 32
1795602702 32
1795602707 32
1795602712 32
1795602717 32
1795602722 32
1795602727 32
1795602732 32
1795602737 32
1795602742 32
1795602747 32
```
</details>

---

