---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:58:02 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1794930714 59
1794930719 59
1794930724 59
1794930729 59
1794930734 59
1794930739 59
1794930744 59
1794930749 59
1794930754 59
1794930759 54
1794930764 54
1794930769 54
1794930774 54
1794930779 54
1794930784 54
1794930789 54
1794930794 54
1794930799 54
1794930804 54
1794930809 54
```
</details>

---

