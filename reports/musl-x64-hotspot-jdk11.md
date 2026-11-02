---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:22:57 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 530 |

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

