---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-02-02 10:12:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770044804 24
1770044809 24
1770044814 24
1770044819 24
1770044824 24
1770044829 24
1770044834 24
1770044839 24
1770044844 24
1770044849 24
1770044854 24
1770044859 24
1770044864 24
1770044869 24
1770044874 24
1770044879 24
1770044884 24
1770044889 24
1770044894 24
1770044899 24
```
</details>

---

