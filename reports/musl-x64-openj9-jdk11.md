---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:34:33 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (5 unique values: 73-82 cores)</summary>

```
1795015794 82
1795015799 82
1795015804 80
1795015809 80
1795015815 81
1795015820 81
1795015825 81
1795015830 81
1795015835 81
1795015840 81
1795015845 81
1795015850 81
1795015855 81
1795015860 81
1795015865 81
1795015870 81
1795015875 81
1795015880 79
1795015885 79
1795015890 73
```
</details>

---

