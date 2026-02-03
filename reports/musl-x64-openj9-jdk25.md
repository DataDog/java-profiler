---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 10:07:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 11 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1087 |
| Sample Rate | 18.12/sec |
| Health Score | 1132% |
| Threads | 13 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1770130809 60
1770130814 60
1770130819 60
1770130824 60
1770130829 60
1770130834 60
1770130839 58
1770130844 58
1770130849 58
1770130854 58
1770130859 58
1770130864 58
1770130869 58
1770130874 58
1770130879 58
1770130884 58
1770130889 58
1770130894 58
1770130899 58
1770130904 58
```
</details>

---

