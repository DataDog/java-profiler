---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 19-34 cores)</summary>

```
1790084779 19
1790084784 19
1790084789 19
1790084794 19
1790084799 19
1790084804 19
1790084809 19
1790084814 19
1790084819 19
1790084824 19
1790084829 19
1790084834 19
1790084839 19
1790084844 34
1790084849 34
1790084854 34
1790084859 34
1790084864 34
1790084869 34
1790084874 34
```
</details>

---

