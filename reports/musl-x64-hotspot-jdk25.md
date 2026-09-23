---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:48:43 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 26-72 cores)</summary>

```
1790171054 41
1790171059 72
1790171064 72
1790171069 47
1790171074 47
1790171079 47
1790171084 47
1790171089 47
1790171094 47
1790171099 47
1790171104 47
1790171109 47
1790171114 47
1790171119 47
1790171124 47
1790171129 47
1790171134 47
1790171139 47
1790171144 47
1790171149 26
```
</details>

---

