---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-11 23:05:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 53-61 cores)</summary>

```
1791774062 61
1791774067 61
1791774072 61
1791774077 61
1791774082 61
1791774087 61
1791774092 61
1791774097 61
1791774102 61
1791774107 61
1791774112 61
1791774117 61
1791774122 61
1791774127 59
1791774132 59
1791774137 59
1791774142 59
1791774147 59
1791774152 59
1791774157 61
```
</details>

---

