---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:12:48 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1794931714 28
1794931719 28
1794931724 28
1794931729 28
1794931734 28
1794931739 28
1794931744 28
1794931749 28
1794931754 28
1794931759 28
1794931764 28
1794931769 28
1794931774 28
1794931779 28
1794931784 28
1794931789 28
1794931794 28
1794931799 28
1794931804 28
1794931809 28
```
</details>

---

