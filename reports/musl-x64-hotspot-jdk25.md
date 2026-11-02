---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 07:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 70-79 cores)</summary>

```
1793621946 70
1793621951 70
1793621956 79
1793621961 79
1793621966 79
1793621971 79
1793621976 79
1793621981 79
1793621986 79
1793621991 79
1793621996 79
1793622001 79
1793622006 79
1793622011 79
1793622016 79
1793622021 79
1793622026 79
1793622031 79
1793622036 79
1793622041 79
```
</details>

---

