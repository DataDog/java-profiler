---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:16:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778173703 64
1778173708 64
1778173713 64
1778173718 59
1778173724 59
1778173729 59
1778173734 59
1778173739 59
1778173744 59
1778173749 59
1778173754 59
1778173759 59
1778173764 59
1778173769 59
1778173774 59
1778173779 59
1778173784 59
1778173789 59
1778173794 59
1778173799 59
```
</details>

---

