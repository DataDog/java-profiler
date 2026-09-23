---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-09-23 16:42:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 86-87 cores)</summary>

```
1790195841 87
1790195846 87
1790195851 87
1790195856 86
1790195861 86
1790195866 86
1790195871 86
1790195876 86
1790195881 86
1790195886 86
1790195891 86
1790195896 86
1790195901 86
1790195906 86
1790195911 86
1790195916 86
1790195921 87
1790195926 87
1790195931 87
1790195936 87
```
</details>

---

