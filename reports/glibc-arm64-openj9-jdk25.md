---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:36:31 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 13 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1795620769 47
1795620774 47
1795620779 47
1795620784 47
1795620789 47
1795620794 42
1795620799 42
1795620804 42
1795620809 42
1795620814 42
1795620819 42
1795620824 42
1795620829 42
1795620834 42
1795620839 42
1795620844 42
1795620849 42
1795620854 42
1795620859 42
1795620864 47
```
</details>

---

