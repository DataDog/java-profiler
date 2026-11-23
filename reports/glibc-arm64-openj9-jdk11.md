---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (5 unique values: 49-59 cores)</summary>

```
1795429070 49
1795429075 49
1795429080 49
1795429085 49
1795429090 49
1795429095 49
1795429100 49
1795429105 49
1795429110 55
1795429115 55
1795429120 55
1795429125 55
1795429130 50
1795429135 50
1795429140 50
1795429145 50
1795429150 59
1795429155 59
1795429160 59
1795429165 54
```
</details>

---

