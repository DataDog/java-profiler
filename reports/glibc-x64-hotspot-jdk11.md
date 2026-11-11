---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:02:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 61-82 cores)</summary>

```
1794427032 82
1794427037 82
1794427042 82
1794427047 82
1794427052 79
1794427057 79
1794427062 79
1794427067 79
1794427072 77
1794427077 77
1794427082 77
1794427087 77
1794427092 77
1794427097 79
1794427102 79
1794427107 79
1794427112 79
1794427117 81
1794427122 81
1794427127 61
```
</details>

---

