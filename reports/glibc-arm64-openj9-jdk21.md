---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 06:13:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1787134025 24
1787134030 24
1787134035 24
1787134040 24
1787134045 24
1787134050 24
1787134055 24
1787134060 24
1787134065 24
1787134070 24
1787134075 24
1787134080 24
1787134085 24
1787134090 24
1787134095 24
1787134100 24
1787134105 44
1787134110 44
1787134115 44
1787134120 44
```
</details>

---

