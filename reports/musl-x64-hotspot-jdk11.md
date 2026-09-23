---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 16:42:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1084 |
| Sample Rate | 18.07/sec |
| Health Score | 1129% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 54-74 cores)</summary>

```
1790195874 54
1790195879 54
1790195884 54
1790195889 54
1790195894 54
1790195899 54
1790195904 54
1790195909 54
1790195914 74
1790195919 74
1790195924 74
1790195929 64
1790195934 64
1790195939 64
1790195944 64
1790195949 64
1790195954 64
1790195959 64
1790195964 64
1790195969 64
```
</details>

---

