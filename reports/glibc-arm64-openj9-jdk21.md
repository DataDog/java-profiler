---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 18:13:00 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 25-47 cores)</summary>

```
1795129729 25
1795129734 25
1795129739 25
1795129744 25
1795129749 25
1795129754 25
1795129759 30
1795129764 30
1795129769 30
1795129774 30
1795129779 30
1795129784 30
1795129789 30
1795129794 30
1795129799 30
1795129804 30
1795129809 30
1795129814 30
1795129819 47
1795129824 47
```
</details>

---

