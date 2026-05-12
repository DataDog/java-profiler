---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 20:52:51 EDT

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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778546971 64
1778546976 64
1778546981 64
1778546986 64
1778546991 64
1778546996 64
1778547001 64
1778547006 64
1778547012 64
1778547017 64
1778547022 64
1778547027 64
1778547032 64
1778547037 64
1778547042 64
1778547047 64
1778547052 64
1778547057 64
1778547062 64
1778547067 64
```
</details>

---

