---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:48:33 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795113774 29
1795113779 29
1795113784 29
1795113789 29
1795113794 29
1795113799 29
1795113804 29
1795113809 29
1795113814 29
1795113819 29
1795113824 29
1795113829 29
1795113834 29
1795113839 29
1795113844 29
1795113849 34
1795113854 34
1795113859 34
1795113864 34
1795113869 34
```
</details>

---

