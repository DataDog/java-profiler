---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 11:55:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 9 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 48-59 cores)</summary>

```
1793289051 59
1793289056 59
1793289061 48
1793289066 48
1793289071 48
1793289076 48
1793289081 48
1793289086 48
1793289091 48
1793289096 48
1793289101 48
1793289106 48
1793289111 48
1793289116 48
1793289121 48
1793289126 48
1793289131 48
1793289136 48
1793289141 48
1793289146 48
```
</details>

---

