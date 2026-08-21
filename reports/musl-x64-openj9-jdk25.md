---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 10:08:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 58-78 cores)</summary>

```
1787320995 58
1787321000 58
1787321005 73
1787321010 73
1787321015 73
1787321020 73
1787321025 73
1787321030 73
1787321035 73
1787321040 73
1787321045 73
1787321050 73
1787321055 73
1787321060 73
1787321065 73
1787321070 73
1787321075 73
1787321080 78
1787321085 78
1787321090 58
```
</details>

---

