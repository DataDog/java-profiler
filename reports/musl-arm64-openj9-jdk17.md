---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-16 12:13:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789574781 32
1789574786 32
1789574791 32
1789574796 32
1789574801 32
1789574806 32
1789574811 32
1789574816 32
1789574821 32
1789574826 32
1789574831 32
1789574836 32
1789574841 32
1789574846 32
1789574851 32
1789574856 32
1789574861 32
1789574866 32
1789574871 32
1789574876 32
```
</details>

---

