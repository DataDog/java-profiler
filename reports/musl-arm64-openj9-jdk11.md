---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:36:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 569 |

<details>
<summary>CPU Timeline (2 unique values: 37-39 cores)</summary>

```
1794594724 37
1794594729 37
1794594734 37
1794594739 39
1794594744 39
1794594749 39
1794594754 39
1794594759 39
1794594764 39
1794594769 39
1794594774 39
1794594779 39
1794594784 39
1794594789 39
1794594794 39
1794594799 39
1794594804 39
1794594809 39
1794594814 39
1794594819 39
```
</details>

---

