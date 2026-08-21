---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 15:09:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1787339106 47
1787339111 47
1787339116 47
1787339121 47
1787339126 47
1787339131 49
1787339136 49
1787339141 49
1787339146 49
1787339151 49
1787339156 49
1787339161 49
1787339166 49
1787339171 49
1787339176 49
1787339181 49
1787339186 49
1787339191 49
1787339196 49
1787339201 49
```
</details>

---

