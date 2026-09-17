---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 10:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 31-34 cores)</summary>

```
1789655028 33
1789655033 33
1789655038 33
1789655043 31
1789655048 31
1789655053 31
1789655058 31
1789655063 31
1789655068 31
1789655073 31
1789655078 31
1789655083 31
1789655088 31
1789655093 31
1789655098 31
1789655103 31
1789655108 31
1789655113 33
1789655118 33
1789655123 33
```
</details>

---

