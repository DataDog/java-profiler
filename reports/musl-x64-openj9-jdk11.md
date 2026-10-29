---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 12:44:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1793291890 88
1793291895 88
1793291900 88
1793291905 88
1793291910 88
1793291915 88
1793291920 90
1793291925 90
1793291931 90
1793291936 90
1793291941 90
1793291946 88
1793291951 88
1793291956 86
1793291961 86
1793291966 86
1793291971 86
1793291976 86
1793291981 86
1793291986 88
```
</details>

---

