---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-11 18:22:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778537918 64
1778537923 64
1778537928 64
1778537933 64
1778537938 64
1778537943 64
1778537948 64
1778537953 64
1778537958 64
1778537963 64
1778537968 64
1778537973 64
1778537978 64
1778537983 64
1778537988 64
1778537993 64
1778537998 64
1778538003 64
1778538008 64
1778538013 64
```
</details>

---

