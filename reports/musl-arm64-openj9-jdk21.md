---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 08:51:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 9 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 34-64 cores)</summary>

```
1787229939 64
1787229944 64
1787229949 64
1787229954 64
1787229959 64
1787229964 64
1787229969 64
1787229974 64
1787229979 64
1787229984 64
1787229989 64
1787229994 64
1787229999 64
1787230004 64
1787230009 64
1787230014 64
1787230019 64
1787230024 64
1787230029 64
1787230034 64
```
</details>

---

