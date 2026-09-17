---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:59:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 12 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1789674939 96
1789674944 96
1789674949 96
1789674954 96
1789674960 96
1789674965 96
1789674970 96
1789674975 96
1789674980 96
1789674985 96
1789674990 88
1789674995 88
1789675000 88
1789675005 88
1789675010 88
1789675015 88
1789675020 88
1789675025 88
1789675030 88
1789675035 88
```
</details>

---

