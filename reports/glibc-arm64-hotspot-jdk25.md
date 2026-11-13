---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:31:28 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794572854 32
1794572859 32
1794572864 32
1794572869 32
1794572874 32
1794572879 32
1794572884 32
1794572889 32
1794572894 32
1794572899 32
1794572904 32
1794572909 32
1794572914 32
1794572919 32
1794572924 32
1794572929 32
1794572934 32
1794572939 32
1794572944 32
1794572949 32
```
</details>

---

