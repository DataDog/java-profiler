---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:36 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 73-75 cores)</summary>

```
1790094085 73
1790094090 73
1790094095 73
1790094100 73
1790094105 73
1790094110 73
1790094115 73
1790094120 73
1790094125 75
1790094130 75
1790094135 75
1790094140 75
1790094145 75
1790094150 75
1790094155 75
1790094160 75
1790094165 75
1790094170 75
1790094175 75
1790094180 75
```
</details>

---

