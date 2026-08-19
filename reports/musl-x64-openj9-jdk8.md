---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-19 13:04:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787158813 96
1787158818 96
1787158823 96
1787158828 96
1787158833 96
1787158838 96
1787158843 96
1787158848 96
1787158853 96
1787158858 96
1787158863 96
1787158868 96
1787158873 96
1787158878 96
1787158883 88
1787158888 88
1787158893 88
1787158898 88
1787158903 88
1787158908 88
```
</details>

---

