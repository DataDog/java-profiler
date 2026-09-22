---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 16.45/sec |
| Health Score | 1028% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1790093716 76
1790093721 76
1790093726 76
1790093731 76
1790093736 76
1790093741 76
1790093746 76
1790093751 76
1790093756 76
1790093761 76
1790093766 76
1790093771 76
1790093776 76
1790093781 76
1790093786 86
1790093791 86
1790093796 86
1790093801 86
1790093806 86
1790093811 86
```
</details>

---

