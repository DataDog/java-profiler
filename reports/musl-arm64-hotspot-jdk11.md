---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 8-28 cores)</summary>

```
1793621915 8
1793621920 28
1793621925 28
1793621930 28
1793621936 28
1793621941 28
1793621946 28
1793621951 28
1793621956 28
1793621961 28
1793621966 8
1793621971 8
1793621976 8
1793621981 8
1793621986 8
1793621991 8
1793621996 8
1793622001 8
1793622006 8
1793622011 8
```
</details>

---

