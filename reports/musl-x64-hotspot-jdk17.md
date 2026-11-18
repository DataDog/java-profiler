---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 07:14:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1795003776 71
1795003781 71
1795003786 79
1795003791 79
1795003796 79
1795003801 79
1795003806 74
1795003811 74
1795003816 74
1795003821 74
1795003826 74
1795003831 74
1795003837 74
1795003842 74
1795003847 74
1795003852 74
1795003857 74
1795003862 74
1795003867 74
1795003872 74
```
</details>

---

