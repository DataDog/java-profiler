---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 04:00:02 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 18-39 cores)</summary>

```
1786607789 18
1786607794 18
1786607799 18
1786607804 18
1786607809 18
1786607814 18
1786607819 18
1786607824 18
1786607829 18
1786607834 18
1786607839 39
1786607844 39
1786607849 39
1786607854 39
1786607859 39
1786607864 39
1786607869 39
1786607874 39
1786607879 39
1786607884 39
```
</details>

---

