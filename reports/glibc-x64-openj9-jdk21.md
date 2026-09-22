---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:14:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1790097025 52
1790097030 52
1790097035 52
1790097040 52
1790097045 52
1790097050 52
1790097055 54
1790097060 54
1790097065 54
1790097070 54
1790097075 54
1790097080 54
1790097085 54
1790097090 54
1790097095 54
1790097100 54
1790097106 54
1790097111 54
1790097116 54
1790097121 54
```
</details>

---

