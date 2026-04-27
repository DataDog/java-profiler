---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 14:05:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777312780 64
1777312785 64
1777312790 64
1777312795 64
1777312800 64
1777312805 64
1777312810 64
1777312815 64
1777312820 64
1777312825 64
1777312830 64
1777312835 64
1777312840 64
1777312845 64
1777312850 64
1777312855 64
1777312860 64
1777312865 64
1777312870 64
1777312875 64
```
</details>

---

